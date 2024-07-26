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

# TODO: Create a .pyx interface with OpenSSL C libraries (and maybe our own C implementation, to make things easier?). Call cythonize here to link to that.

root = path.abspath(__file__ + "/../pages/")

class Parser(HTMLParser):
	def __init__(self, convert_charrefs: bool = True) -> None:
		super().__init__(convert_charrefs=convert_charrefs)

	# TODO: Handle replacing <a> tags with their randomly generated password.
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