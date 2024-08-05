from ctypes import cdll, c_size_t, create_string_buffer
from os import path, scandir, remove
from sys import argv

cryptsab = cdll.LoadLibrary("cryptsab/build/libcryptsab.dll")

def readFiles(dir, relative_path=""):
	foldername, ext = path.splitext(dir.name)

	files = []
	for entry in scandir(dir):
		if entry.is_dir():
			files = files + readFiles(entry, f"{foldername}/")
		
		filename, extension = path.splitext(entry.name)

		if extension == ".html":
			files.append(f"{relative_path}{foldername}/{entry.name}".encode("utf-8"))
	return files

def searchDir(dir):
	files_to_compress = readFiles(dir)

	foldername, ext = path.splitext(dir.name)
	tarname = f"{foldername}.tar.z"
	
	cryptsab.tar_z_compress(tarname.encode("utf-8"), f"pages/".encode("utf-8"), len(files_to_compress), *files_to_compress)

	return tarname.encode('utf-8')

if __name__ == "__main__":
	if len(argv) < 2:
		raise "Need to set out archive."
	tar_files = []
	for pagefolder in scandir(path.abspath(__file__ + "/../pages/")):
		filename, extension = path.splitext(pagefolder.name)
		if not pagefolder.is_dir():
			print(filename, " is not a folder.")
			continue
		tar_files.append(searchDir(pagefolder))
	
	cryptsab.tar_z_compress(argv[1].encode("utf-8"), "".encode("utf-8"), len(tar_files), *tar_files)

	for file in tar_files:
		remove(file)