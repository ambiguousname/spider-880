from ctypes import cdll
from os import path, scandir

cryptsab = cdll.LoadLibrary("cryptsab.dll")

def searchDir(dir):
	for entry in scandir(dir):
		filename, extension = path.splitext(entry.name)
		if entry.is_dir():
			searchDir(entry)
		elif extension == ".html":
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
	searchDir(path.abspath(__file__ + "/../pages/"))