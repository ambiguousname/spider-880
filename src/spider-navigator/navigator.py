# Should be run as part of the build step.
# Create .cpp for each detected file in the /pages/ directory to be bundled with the .exe.
# Requires Python >=3.11.4

from html.parser import HTMLParser
from os import PathLike, path, scandir, sep
import re
import io

class HtmlStackNode():
	headers = set()
	tabs = 2
	def __init__(self, stream, id : int, tag : str, attrs: list[tuple[str, str | None]], x : int, y : int, w : int, h : int) -> None:
		self.tag = tag
		self.attrs = {}
		self.id = id
		for attr in attrs:
			self.attrs[attr[0]] = attr[1]
		if "id" in self.attrs:
			self.id = self.attrs["id"]
				
		self.x = x
		self.y = y
		self.w = w
		self.h = h
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
	headers = ["<FL/Fl_Window.h>"]

	def open(self):
		if "x" in self.attrs:
			self.x = int(self.attrs["x"])

		if "y" in self.attrs:
			self.y = int(self.attrs["y"])
		
		if "w" in self.attrs:
			self.w = int(self.attrs["w"])
		
		if "h" in self.attrs:
			self.h = int(self.attrs["h"])
		
		self.writeln(f"Fl_Window *window = new Fl_Window({self.x}, {self.y}, {self.w}, {self.h}, \"{self.id}\");")
	
	def close(self):
		self.writeln("window->end();")
		self.writeln("window->show();")

class PNode(HtmlStackNode):
	headers = ["<FL/Fl_Group.h>", "<FL/Fl_Output.h>"]
	text_id = 0

	def open(self):
		self.writeln(f"Fl_Group *p_{self.id} = new Fl_Group({self.x}, {self.y}, {self.w}, {self.h});")
	
	def data(self, data):
		lines = data.split("\n")
		for line in lines:
			if line and not str.isspace(line):
				self.writeln(f"Fl_Output *p_{self.id}_text_{self.text_id} = new Fl_Output({self.x}, {self.y * (20 * self.text_id)}, {self.w}, {self.h}, \"{line.lstrip()}\");")
				self.text_id += 1

	def close(self):
		self.writeln(f"p_{self.id}->end();")

class Script(HtmlStackNode):
	tabs = 1
	def data(self, data):
		lines = data.split("\n")
		num_tabs = lines[1].count('\t')
		for line in lines:
			self.writeln(line.replace('\t' * num_tabs, ""))

class Headers(HtmlStackNode):
	def data(self, data):
		lines = data.split("\n")
		for line in lines:
			if len(line) > 0 and not str.isspace(line):
				self.headers.add(line.lstrip())
		return super().data(data)

class HTMLCPPParser(HTMLParser):
	def __init__(self, p, convert_charrefs: bool = True) -> None:
		super().__init__(convert_charrefs=convert_charrefs)

		self.path = p

		self.cpp_stream = io.StringIO()
		self.draw_stream = io.StringIO("void draw() {\n")
		self.custom_script_dat = io.StringIO()

		self.id = 0

		self.stack = []
		self.headers = set()


		matches = re.match(".*pages(.*)", path.splitext(p)[0])
		self.namespace = matches[1].replace(sep, " ").replace("_", " ").title().replace(" ", "")


	def close(self):
		self.cpp_stream.write(f"namespace {self.namespace} {{")
		self.custom_script_dat.seek(0)
		self.cpp_stream.write(self.custom_script_dat.read())
		self.draw_stream.seek(0)
		self.cpp_stream.write("\tvoid draw() {\n")
		self.cpp_stream.write(self.draw_stream.read())
		self.cpp_stream.write("\t\tonStart();\n\t}\n}")

		self.custom_script_dat.close()
		self.draw_stream.close()
		if len(self.stack) > 0:
			print("Unclosed tags: " + self.stack)

	def match_node(self):
		return {
			"p": {"type": PNode, "stream": self.draw_stream},
			"body": {"type": Body, "stream": self.draw_stream},
			"script": {"type": Script, "stream": self.custom_script_dat},
			"headers": {"type": Headers, "stream": self.draw_stream}
		}

	def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
		self.id += 1
		
		info = self.match_node().get(tag, {"type": HtmlStackNode, "stream": self.draw_stream})
		node = None
		if len(self.stack) > 0:
			prev = self.stack[-1]
			node = info["type"](info["stream"], self.id, tag, attrs, prev.x, prev.y, prev.w, prev.h)
		else:
			node = info["type"](info["stream"], self.id, tag, attrs, 0, 0, 100, 100)
		node.open()
		self.stack.append(node)
		return super().handle_starttag(tag, attrs)

	def handle_endtag(self, tag: str) -> None:
		if self.stack[-1].tag != tag:
			print("Error: starting tag not found for " + str(self.stack[-1]))
		else:
			closing = self.stack.pop()
			self.headers.update(closing.headers)
			closing.close()
		return super().handle_endtag(tag)
	
	def handle_data(self, data: str) -> None:
		if len(self.stack) > 0:
			self.stack[-1].data(data)
		return super().handle_data(data)
		

def searchDir(dir : PathLike):
	cpp_to_write = []
	headers = set()
	for entry in scandir(dir):
		print("Found: ", entry.name)
		filename, extension = path.splitext(entry.name)
		if entry.is_dir():
			searchDir(entry)
		elif extension == ".cpphtml":
			print("Reading...")
			with open(entry.path, "r") as file:
				base, full_filename = path.split(entry.path)
				parser = HTMLCPPParser(path.join(base, filename + ".cpp"))
				parser.feed(file.read())
				parser.close()
				headers.update(parser.headers)
				cpp_to_write.append((parser.cpp_stream, parser.namespace))
	
	header = open(path.join(dir, "/pages.h"), "w")
	cpp = open(path.join(dir, "/pages.cpp"), "w")

	for header in headers:
			headers.write(f"#include {header}\n")


	for stream, namespace in cpp_to_write:
		cpp.write(stream.read())
		stream.close()



	header.close()
	cpp.close()



		

if __name__ == "__main__":
	searchDir(path.abspath(__file__ + "/../pages/"))