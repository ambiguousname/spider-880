# Should be run as part of the build step.
# Create .cpp for each detected file in the /pages/ directory to be bundled with the .exe.
#include <string>
#include <iostream>
#include <filesystem>

from html.parser import HTMLParser
from os import PathLike, path, scandir

BOILERPLATE = """
#include <iostream>
#include <FL/Fl_Window.h>
#include <FL/Fl_Box.h>
#include <FL/Fl_Group.h>

void draw() {
	Fl_Window *window = new Fl_Window(340, 480, "Test");
"""

class HtmlStackNode():
	def __init__(self, id : int, tag : str, attrs: list[tuple[str, str | None]]) -> None:
		self.tag = tag
		self.attrs = attrs
		self.id = id
		for attr in attrs:
			if attr[0] == "id":
				self.id = attr[1]
	
	def __str__(self) -> str:
		return str(self.tag) + " - " + str(self.id)

	def __eq__(self, __value: object) -> bool:
		return __value == self.tag

class HTMLCPPParser(HTMLParser):
	def __init__(self, path, convert_charrefs: bool = True) -> None:
		super().__init__(convert_charrefs=convert_charrefs)

		self.cpp_file = open(path, 'w')
		self.cpp_file.write(BOILERPLATE)

		self.script_dat = ""

		self.id = 0

		self.x = 0
		self.y = 0

		self.w = 100
		self.h = 100

		self.stack = []

	def close(self):
		self.cpp_file.write("\twindow->end();\n\twindow->show();\n\tonStart();\n}\n")
		self.cpp_file.write(self.script_dat)
		self.cpp_file.close()
		if len(self.stack) > 0:
			print("Unclosed tags: " + self.stack)


	def handle_starttag(self, tag: str, attrs: list[tuple[str, str | None]]) -> None:
		self.id += 1
		node = HtmlStackNode(self.id, tag, attrs)
		if "body" in self.stack:
			match tag:
				case "p":
					self.cpp_file.write(f"\tFl_Group *p_{node.id} = new Fl_Group({self.x}, {self.y}, {self.w}, {self.h});\n")
		self.stack.append(node)
		return super().handle_starttag(tag, attrs)

	def handle_endtag(self, tag: str) -> None:
		if self.stack[-1].tag != tag:
			print("Error: starting tag not found for " + self.stack[-1])
		else:
			closing = self.stack.pop()
			if "body" in self.stack:
				match tag:
					case "p":
						self.cpp_file.write(f"\tp_{str(closing.id)}->end();\n")
		return super().handle_endtag(tag)
	
	def handle_data(self, data: str) -> None:
		curr_tag = self.stack[-1].tag
		if curr_tag == "script":
			lines = data.split("\n")
			num_tabs = lines[1].count('\t')
			for line in lines:
				self.script_dat += line.replace('\t' * num_tabs, "") + "\n"
		return super().handle_data(data)

		

def searchDir(dir : PathLike):
	print(dir)
	for entry in scandir(dir):
		print("Found: ", entry.name, "\n")
		filename, extension = path.splitext(entry.name)
		if entry.is_dir():
			searchDir(entry)
		elif extension == ".cpphtml":
			with open(entry.path, "r") as file:
				base, full_filename = path.split(entry.path)
				parser = HTMLCPPParser(path.join(base, filename + ".cpp"))
				parser.feed(file.read())
				parser.close()

		

if __name__ == "__main__":
	searchDir(path.abspath(__file__ + "/../pages/"))