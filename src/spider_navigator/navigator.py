# Should be run as part of the build step.
# Create .cpp for each detected file in the /pages/ directory to be bundled with the .exe.
# Requires Python >=3.11.4

from html.parser import HTMLParser
from os import PathLike, path, sep, scandir
import re
import io
import sys

root = path.abspath(__file__ + "/../pages/")

supported_nodes = set()
with open(path.join(root, "../page.h"), "r") as f:
	found_types = False
	for line in f.readlines():
		if len(line) <= 0 or str.isspace(line):
			continue
		if "NodeType" in line:
			found_types = True
			continue
		if found_types:
			if "}" in line:
				break
			if "DEFAULT" in line:
				continue
			supported_nodes.add(line.replace(",","").replace("\n", "").lstrip())

class HtmlStackNode():
	
	def __init__(self, id : str, tag : str, attrs: list[tuple[str, str | None]], parent = None, prev = None) -> None:
		self.includes = set()

		self.element_stream = io.StringIO()

		self.tag = None
		self.parent = None
		self.children = []
		self.attrs = {}
		self.dat = ""

		self.tag = tag
		self.id = id

		for attr in attrs:
			self.attrs[attr[0]] = attr[1]

		if "id" in self.attrs:
			self.id = self.attrs["id"]

		self.prev = prev
		self.parent = parent
	
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

	invisible = False
	def close(self):
		if not self.invisible:
			self.writeln(f"const HTMLNode {self} = {{")

			if self.tag.upper() in supported_nodes:
				self.writeln(f"\t{self.tag.upper()},")
			else:
				self.writeln("\tDEFAULT,")
			self.writeln(f"\t\"{self.dat}\",")
			self.writeln("\t{")
			for child in self.children:
				if not child.invisible:
					self.writeln(f"\t\tmake_shared<HTMLNode>({child}),")
			self.writeln("\t},")
			self.writeln("\t{")
			for attr, val in self.attrs.items():
				self.writeln(f"\t\t{{\"{attr}\", \"{val}\"}},")
			self.writeln("\t},")
			self.writeln("};")

class ImageNode(HtmlStackNode):
	includes = ["<util/image_box.h>"]

class PNode(HtmlStackNode):
	def data(self, data):
		lines = data.replace("\"", "\\\"").split("\n")
		for line in lines:
			self.dat += line.lstrip()

class Script(HtmlStackNode):
	invisible = True
	def data(self, data):
		lines = data.split("\n")
		num_tabs = lines[1].count('\t')
		for line in lines:
			if len(line) > 0 and not str.isspace(line):
				self.writeln(line.replace('\t' * num_tabs, ""))
	
	def close(self):
		return

class Includes(HtmlStackNode):
	invisible = True
	def data(self, data):
		lines = data.split("\n")
		for line in lines:
			if len(line) > 0 and not str.isspace(line):
				self.includes.add(line.lstrip())
		return super().data(data)

class Header(HtmlStackNode):
	pass

class HTMLCPPParser(HTMLParser):
	def __init__(self, stream, p, convert_charrefs: bool = True) -> None:
		super().__init__(convert_charrefs=convert_charrefs)

		self.path = p

		self.cpp_stream = stream
		self.struct_stream = io.StringIO()
		self.custom_script_dat = io.StringIO()

		self.id = 0

		self.stack = []
		self.includes = set(["<FL/Fl.h>", "\"spider_navigator/page.h\""])

		self.prev = None


		matches = re.match(".*pages(.*)", path.splitext(p)[0])
		self.namespace = matches[1].replace(sep, " ").replace("_", " ").title().replace(" ", "") + "HTMLWindow"


	def close(self):
		self.cpp_stream.write(f"#include \"pages.h\"\n")
		
		self.custom_script_dat.seek(0)
		self.cpp_stream.write(self.custom_script_dat.read())

		self.struct_stream.seek(0)
		self.cpp_stream.write(self.struct_stream.read())

		self.cpp_stream.write(f"{self.namespace}::{self.namespace}(int x, int y, int w, int h) : HTMLWindow(make_shared<HTMLNode>(html_1), x, y, w, h) {{\n\n}}")

		self.custom_script_dat.close()
		self.struct_stream.close()
		if len(self.stack) > 0:
			sys.stderr.write("Unclosed tags: " + self.stack)

	def match_node(self):
		return {
			"script": Script,
			"includes": Includes,
			"p": PNode,
			"img": ImageNode
		}

	def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
		self.id += 1
		
		info = self.match_node().get(tag, HtmlStackNode)
		node = None
		if len(self.stack) > 0:
			prev = self.stack[-1]
			node = info(self.id, tag, attrs, prev)
			prev.append(node)
		else:
			node = info(self.id, tag, attrs)
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
			if closing is Script:
				self.custom_script_dat.write(closing.element_stream.read())
			else:
				self.struct_stream.write(closing.element_stream.read())
			closing.element_stream.close()
		return super().handle_endtag(tag)
	
	def handle_data(self, data: str) -> None:
		if len(self.stack) > 0:
			self.stack[-1].data(data)
		return super().handle_data(data)

def searchDir(dir):
	includes = set()
	header_info = []
	num_entries = 0

	for entry in scandir(dir):
		filename, extension = path.splitext(entry.name)
		if entry.is_dir():
			searchDir(entry)
		elif extension == ".cpphtml":
			num_entries += 1

			entry_path = path.abspath(entry.path)
			base, full_filename = path.split(entry_path)
			pth = path.join(base, filename + ".cpp")

			cpp_stream = open(pth, "w")
			parser = HTMLCPPParser(cpp_stream, pth)
			file = open(entry.path, "r")
			parser.feed(file.read())
			parser.close()
			file.close()
			
			includes.update(parser.includes)
			header_info.append(parser.namespace)
			
			f = open(path.join(root, "../list.txt"), "a")
			f.write(pth + "\n")
			f.close()
	
	if num_entries > 0:
		header = open(path.join(dir, "pages.h"), "w")
		header.write("#pragma once\n")

		for include in includes:
			header.write(f"#include {include}\n")

		for namespace in header_info:
			header.write(f"class {namespace} : public HTMLWindow {{\n\tpublic:\n\t{namespace}(int x, int y, int w, int h);\n}};\n")
		header.close()

if __name__ == "__main__":
	f = open(path.join(root, "../list.txt"), "w")
	f.truncate()
	f.close()
	searchDir(root)