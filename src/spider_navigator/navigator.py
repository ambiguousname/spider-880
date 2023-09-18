# Should be run as part of the build step.
# Create .cpp for each detected file in the /pages/ directory to be bundled with the .exe.
# Requires Python >=3.11.4

from html.parser import HTMLParser
from os import PathLike, path, sep, scandir
import re
import io
import sys

root = path.abspath(__file__ + "/../pages/")

class HtmlStackNode():
	includes = set()
	tabs = 2
	def __init__(self, stream, id : int, tag : str, attrs: list[tuple[str, str | None]], parent = None) -> None:
		self.tag = tag
		self.attrs = {}
		self.id = id
		for attr in attrs:
			self.attrs[attr[0]] = attr[1]
		if "id" in self.attrs:
			self.id = self.attrs["id"]
				
		self.x = 0
		self.y = 0
		self.w = 300
		self.h = 300

		self.parent = parent
		if parent != None:
			self.w = self.parent.w
			self.h = self.parent.h
		
		if "x" in self.attrs:
			self.x = int(self.attrs["x"])

		if "y" in self.attrs:
			self.y = int(self.attrs["y"])
		
		if "w" in self.attrs:
			self.w = int(self.attrs["w"])
		
		if "h" in self.attrs:
			self.h = int(self.attrs["h"])
		self.stream = stream
	
	def writeln(self, line):
		self.stream.write(("\t" * self.tabs) + line + "\n")
	
	def __str__(self) -> str:
		return str(self.tag) + " - " + str(self.id)

	def __eq__(self, __value: object) -> bool:
		return __value == self.tag
	
	def open(self):
		pass

	def data(self, data):
		return

	def close(self):
		pass

class Body(HtmlStackNode):
	includes = ["<FL/Fl_Window.h>"]

	def open(self):
		self.writeln(f"Fl_Window *window = new Fl_Window({self.x}, {self.y}, {self.w}, {self.h}, \"{self.id}\");")
	
	def close(self):
		self.writeln("window->end();")
		self.writeln("window->resizable(*window);")
		self.writeln("window->show();")

class PNode(HtmlStackNode):
	includes = ["<FL/Fl_Text_Display.h>", "<Fl/Fl_Text_Buffer.h>"]

	styles = [{ "color": "FL_FOREGROUND_COLOR", "font": "FL_COURIER", "size": "16" }]

	def open(self):
		self.writeln(f"Fl_Text_Display *p_{self.id} = new Fl_Text_Display({self.x}, {self.y}, {self.w}, {self.h});")
		self.writeln(f"p_{self.id}->box(FL_NO_BOX);")

		self.writeln(f"Fl_Text_Buffer *p_{self.id}_text = new Fl_Text_Buffer();")
		self.writeln(f"Fl_Text_Buffer *p_{self.id}_style = new Fl_Text_Buffer();")
		self.writeln(f"p_{self.id}->buffer(p_{self.id}_text);")
	
	def data(self, data):
		lines = data.replace('"', "\\\"").split("\n")
		for line in lines:
			if len(line) > 0 and not str.isspace(line):
				self.writeln(f"p_{self.id}_text->append(\"{line.lstrip()}\");")
				self.writeln(f"p_{self.id}_style->append(\"{'A' * len(line.lstrip())}\");")
		
	def close(self):
		self.writeln(f"Fl_Text_Display::Style_Table_Entry p_{self.id}_style_table[] = {{")
		for style in self.styles:
			color = style["color"]
			font = style["font"]
			size = style["size"]
			self.writeln(f"\t {{ {color}, {font}, {size} }},")
		self.writeln("};")
		self.writeln(f"p_{self.id}->highlight_data(p_{self.id}_style, p_{self.id}_style_table, {len(self.styles)}, 'A', 0, 0);")
		self.writeln(f"p_{self.id}->wrap_mode(3, 0);")

class ImageNode(HtmlStackNode):
	includes = ["<util/image_box.h>"]

	def open(self):
		if "src" in self.attrs:
			self.writeln(f"ImageBox *img_{self.id} = new ImageBox(\"{self.attrs['src']}\", {self.x}, {self.y}, {self.w}, {self.h});")
		else:
			sys.stderr.write("Could not find source for image box with ID: " + self.id)

class Script(HtmlStackNode):
	tabs = 1
	def data(self, data):
		lines = data.split("\n")
		num_tabs = lines[1].count('\t')
		for line in lines:
			self.writeln(line.replace('\t' * num_tabs, ""))

class Includes(HtmlStackNode):
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
		self.draw_stream = io.StringIO("void draw() {\n")
		self.custom_script_dat = io.StringIO()

		self.id = 0

		self.stack = []
		self.includes = set(["<FL/Fl.h>"])


		matches = re.match(".*pages(.*)", path.splitext(p)[0])
		self.namespace = matches[1].replace(sep, " ").replace("_", " ").title().replace(" ", "") + "HTMLPage"


	def close(self):
		self.cpp_stream.write(f"#include \"pages.h\"\n")
		self.cpp_stream.write(f"namespace {self.namespace} {{")
		self.custom_script_dat.seek(0)
		self.cpp_stream.write(self.custom_script_dat.read())
		self.draw_stream.seek(0)
		self.cpp_stream.write("\tvoid draw() {\n")
		self.cpp_stream.write(self.draw_stream.read())
		self.cpp_stream.write("\t\tonStart();\n\tFl::run();\n\t}\n}")

		self.custom_script_dat.close()
		self.draw_stream.close()
		if len(self.stack) > 0:
			sys.stderr.write("Unclosed tags: " + self.stack)

	def match_node(self):
		return {
			"p": {"type": PNode, "stream": self.draw_stream},
			"body": {"type": Body, "stream": self.draw_stream},
			"script": {"type": Script, "stream": self.custom_script_dat},
			"includes": {"type": Includes, "stream": self.draw_stream},
			"img": {"type": ImageNode, "stream": self.draw_stream}
		}

	def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
		self.id += 1
		
		info = self.match_node().get(tag, {"type": HtmlStackNode, "stream": self.draw_stream})
		node = None
		if len(self.stack) > 0:
			prev = self.stack[-1]
			node = info["type"](info["stream"], self.id, tag, attrs, prev)
		else:
			node = info["type"](info["stream"], self.id, tag, attrs)
		node.open()
		self.stack.append(node)
		return super().handle_starttag(tag, attrs)

	def handle_endtag(self, tag: str) -> None:
		if self.stack[-1].tag != tag:
			sys.stderr.write("Error: starting tag not found for " + str(self.stack[-1]))
		else:
			closing = self.stack.pop()
			self.includes.update(closing.includes)
			closing.close()
		return super().handle_endtag(tag)
	
	def handle_data(self, data: str) -> None:
		if len(self.stack) > 0:
			self.stack[-1].data(data)
		return super().handle_data(data)

def writeHeader(pth, includes, header_info):
	header = open(path.join(pth, "pages.h"), "w")
	header.write("#pragma once\n")

	for include in includes:
		header.write(f"#include {include}\n")

	for namespace in header_info:
		header.write(f"namespace {namespace} {{\n\tvoid draw();\n}}\n")

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
			header.write(f"namespace {namespace} {{\n\tvoid draw();\n}}\n")
		header.close()

if __name__ == "__main__":
	f = open(path.join(root, "../list.txt"), "w")
	f.truncate()
	f.close()
	searchDir(root)