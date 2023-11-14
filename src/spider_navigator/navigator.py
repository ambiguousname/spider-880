# Should be run as part of the build step.
# Create .cpp for each detected file in the /pages/ directory to be bundled with the .exe.
# Requires Python >=3.11.4
# TODO: Namespace to class

from html.parser import HTMLParser
from os import PathLike, path, sep, scandir
import re
import io
import sys
from hashlib import md5

root = path.abspath(__file__ + "/../pages/")

supported_nodes = set()
with open(path.join(root, "../tags.h"), "r") as f:
	found_types = False
	structs = re.findall("class (\w+)", f.read())
	for node in structs:
		supported_nodes.add(node)

def get_camel_case(string):
	return string.replace(sep, " ").replace("_", " ").title().replace(" ", "")

class HtmlStackNode():
	
	def __init__(self, id : str, tag : str, attrs: list[tuple[str, str | None]], parent = None, reader=None) -> None:
		# What .h files to include
		self.includes = set()

		# The string output from this element (structure information).
		self.element_stream = io.StringIO()

		self.parent = parent
		self.children = []
		self.attrs = {}
		# Internal content (like text)
		self.dat = ""

		self.tag = tag
		self.id = id

		# Inheritance:
		if self.parent is not None:
			for attr in self.parent.attrs.items():
				# Avoid inheriting unnecessary attributes:
				# TODO: This should be done with a <style> tag instead.
				if attr[0] == 'title':
					continue
				self.attrs[attr[0]] = attr[1]

		for attr in attrs:
			self.attrs[attr[0]] = attr[1]

		if "id" in self.attrs:
			self.id = self.attrs["id"]

		# Current HTML reader
		self.reader = reader
	
	def append(self, child):
		self.children.append(child)

	def writeln(self, line):
		self.element_stream.write(line + "\n")
	
	def __str__(self) -> str:
		return str(self.tag) + "_" + str(self.id)
	
	def open(self):
		return

	def data(self, data):
		if not str.isspace(data):
			self.dat += data
		return

	# Do we write this as a struct?
	# data() will be called on this if true. Otherwise a child TextNode will be created.
	invisible = False
	def close(self):
		if not self.invisible:
			struct_type = "HTMLNode"
			camel_case = get_camel_case(self.tag)
			if camel_case in supported_nodes:
				struct_type = camel_case
			self.writeln(f"std::shared_ptr<{struct_type}> {self} = std::make_shared<{struct_type}>(")

			self.writeln(f"\t\"{self.dat}\",")
			self.writeln("\tstd::vector<std::shared_ptr<HTMLNode>>{")
			self.children.reverse()
			for child in self.children:
				if not child.invisible:
					self.writeln(f"\t\t{child},")
			self.writeln("\t},")
			self.writeln("\tstd::unordered_map<std::string, std::string>{")
			for attr, val in self.attrs.items():
				self.writeln(f"\t\t{{\"{attr}\", \"{val}\"}},")
			self.writeln("\t}")
			self.writeln(");")

class TextNode(HtmlStackNode):
	def data(self, data):
		lines = data.replace("\"", "\\\"").split("\n")
		for line in lines:
			self.dat += line.lstrip('\t')

class ImageNode(HtmlStackNode):
	includes = ["<util/image_box.h>"]

class ANode(HtmlStackNode):
	def __init__(self, id : str, tag : str, attrs: list[tuple[str, str | None]], parent = None, reader=None):
		super().__init__(id, tag, attrs, parent, reader)
		self.attrs["color"] = "4"

	def open(self):
		if "href" in self.attrs:
			pages_link = (self.attrs["href"] + ".h").replace("\\", "/")
			self.includes.add(f"<{pages_link}>")
			if self.reader is not None:
				abs_path = path.abspath(path.join(root, self.attrs["href"]))
				self.reader.linked_pages.append((self.attrs["href"], get_namespace_from_path(abs_path)))
		return super().open()

class Script(HtmlStackNode):
	invisible = True
	def data(self, data):
		lines = data.split("\n")
		num_tabs = lines[1].count('\t')
		for line in lines:
			if len(line) > 0 and not str.isspace(line):
				self.reader.custom_script_dat.write(line.replace('\t' * num_tabs, "").replace("$CLASS$", self.reader.namespace) + "\n")
	
class Links(HtmlStackNode):
	invisible = True
	def data(self, data):
		lines = data.split("\n")
		for l in lines:
			if self.reader is not None:
				line = l.lstrip()
				if len(line) > 0 and not str.isspace(line):
					abs_path = path.abspath(path.join(root, line))
					self.includes.add(f"<{line}.h>")
					self.reader.linked_pages.append((line, get_namespace_from_path(abs_path)))

class Includes(HtmlStackNode):
	invisible = True
	def data(self, data):
		lines = data.split("\n")
		for line in lines:
			if len(line) > 0 and not str.isspace(line):
				self.includes.add(line.lstrip())

class Header(HtmlStackNode):
	invisible=True
	def data(self, data):
		lines = data.split("\n")
		num_tabs = lines[1].count('\t')
		for line in lines:
			if len(line) > 0 and not str.isspace(line):
				self.reader.header_dat.write("\t" + line.replace('\t' * num_tabs, "").replace("$CLASS$", self.reader.namespace) + "\n")

class Constructor(HtmlStackNode):
	invisible=True
	def data(self, data):
		lines = data.split("\n")
		num_tabs = lines[1].count('\t')
		for line in lines:
			if len(line) > 0 and not str.isspace(line):
				self.reader.constructor_dat.write("\t" + line.replace('\t' * num_tabs, "").replace("$CLASS$", self.reader.namespace) + "\n")

def get_namespace_from_path(p):
	rel = path.relpath(p, root)
	return get_camel_case(rel.replace(".cpp", "")) + "HTMLWindow"

class HTMLCPPParser(HTMLParser):
	def __init__(self, stream, p, convert_charrefs: bool = True) -> None:
		super().__init__(convert_charrefs=convert_charrefs)

		self.path = p

		self.cpp_stream = stream
		# TODO: Four different streams? This suuuucks.
		self.struct_stream = io.StringIO()
		self.custom_script_dat = io.StringIO()
		self.header_dat = io.StringIO()
		self.constructor_dat = io.StringIO()
		self.linked_pages = []

		self.id = 0

		self.stack = []
		self.includes = set(["\"spider_navigator/page.h\""])

		self.prev = None

		self.namespace = get_namespace_from_path(p)


	def close(self):
		header_name = path.split(self.path)[1].replace(".cpp", ".h")
		self.cpp_stream.write(f"#include \"{header_name}\"\n")

		self.custom_script_dat.seek(0)
		self.cpp_stream.write(self.custom_script_dat.read())
		
		self.cpp_stream.write(f"namespace {self.namespace}Namespace {{\n")

		self.struct_stream.seek(0)
		self.cpp_stream.write(self.struct_stream.read())

		self.cpp_stream.write("}\n")

		linked_page_str = ""
		for i in range(len(self.linked_pages)):
			href, page = self.linked_pages[i]
			linked_page_str += f"\tlinked_windows.insert({{\"{href}\", {page}::createWindow}});\n"

		self.cpp_stream.write(f"{self.namespace}::{self.namespace}(int x, int y, int w, int h) : HTMLWindow({self.namespace}Namespace::html_1, x, y, w, h) {{\n{linked_page_str}\n")

		self.constructor_dat.seek(0)
		self.cpp_stream.write(self.constructor_dat.read())

		self.cpp_stream.write("\nend();\n}\n")

		header = open(path.join(self.path, f"../{header_name}"), "w")
		header.write("#pragma once\n")

		for include in self.includes:
			header.write(f"#include {include}\n")

		self.header_dat.seek(0)

		header.write(f"class {self.namespace} : public HTMLWindow {{\n")
		header.write(self.header_dat.read())
		header.write(f"\tpublic:\n\t{self.namespace}(int x, int y, int w, int h);\n\tstatic HTMLWindow* createWindow(int x, int y, int w, int h) {{\n\t\treturn new {self.namespace}(x, y, w, h);\n\t}}\n}};\n")
		header.close()

		self.struct_stream.close()
		self.custom_script_dat.close()
		self.constructor_dat.close()
		self.cpp_stream.close()
		self.header_dat.close()
		if len(self.stack) > 0:
			sys.stderr.write(self.path, "Unclosed tags: " + str(self.stack))

	def match_node(self):
		return {
			"script": Script,
			"includes": Includes,
			"a": ANode,
			"img": ImageNode,
			"links": Links,
			"header": Header,
		}

	def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
		self.id += 1
		
		info = self.match_node().get(tag, HtmlStackNode)
		node = None
		if len(self.stack) > 0:
			prev = self.stack[-1]
			node = info(self.id, tag, attrs, prev, self)
			prev.append(node)
		else:
			node = info(self.id, tag, attrs, None, self)
		node.open()
		self.stack.append(node)
		return super().handle_starttag(tag, attrs)

	def handle_endtag(self, tag: str) -> None:
		if self.stack[-1].tag != tag:
			sys.stderr.write("Error: starting tag not found for " + str(self.stack[-1]))
		else:
			closing = self.stack.pop()
			self.prev = closing
			self.includes.update(closing.includes)
			closing.close()
			closing.element_stream.seek(0)
			self.struct_stream.write(closing.element_stream.read())
			closing.element_stream.close()
		return super().handle_endtag(tag)
	
	def handle_data(self, data: str) -> None:
		if len(self.stack) > 0 and not str.isspace(data):
			prev = self.stack[-1]

			if prev.invisible:
				prev.data(data)
			else:
				attr_list = []
				for key, attr in prev.attrs.items():
					attr_list.append((key, attr))

				node = TextNode(self.id, "text", attr_list, prev, self)
				node.data(data)
				node.close()
				node.element_stream.seek(0)
				self.struct_stream.write(node.element_stream.read())
				node.element_stream.close()

				prev.append(node)

				self.id += 1
		return super().handle_data(data)

def searchDir(dir):
	for entry in scandir(dir):
		filename, extension = path.splitext(entry.name)
		if entry.is_dir():
			searchDir(entry)
		elif extension == ".cpphtml":
			entry_path = path.abspath(entry.path)
			base, full_filename = path.split(entry_path)
			pth = path.join(base, filename + ".cpp")

			file = open(entry.path, "rb")
			file.seek(0)
			hashed = md5(file.read()).hexdigest()
			file.close()

			file = open(entry.path, "r")
			global hashes
			if pth not in hashes or hashed != hashes[pth]:
				cpp_stream = open(pth, "w")
				parser = HTMLCPPParser(cpp_stream, pth)
				parser.feed(file.read())
				parser.close()
				cpp_stream.close()
			
			f = open(path.join(root, "../list.txt"), "a")
			f.write(pth + "\n")
			f.close()

			hash_file = open(path.join(root, "../hash.txt"), "a")
			hash_file.write(hashed + "\n")
			hash_file.close()

if __name__ == "__main__":
	global hashes
	hashes = {}

	list_path = path.join(root, "../list.txt")

	if not path.exists(list_path):
		open(list_path, "w").close()

	f = open(list_path, "r+")

	hash_list_pth = path.join(root, "../hash.txt")
	if not path.exists(hash_list_pth):
		new_f = open(hash_list_pth, "w")
		new_f.close()
	hash_list = open(hash_list_pth, "r+")
	for line in f.readlines():
		hashes[line.lstrip().replace("\n", "")] = hash_list.readline().lstrip().replace("\n", "")
	hash_list.seek(0)
	hash_list.truncate()

	f.seek(0)
	f.truncate()
	f.close()
	searchDir(root)