from ctypes import cdll, c_size_t, create_string_buffer
from os import path, scandir

cryptsab = cdll.LoadLibrary("cryptsab/build/libcryptsab.dll")

def searchDir(dir):
	foldername, ext = path.splitext(dir.name)

	files_to_compress = []
	for entry in scandir(dir):
		filename, extension = path.splitext(entry.name)

		if extension == ".html":
			files_to_compress.append("pages/{}/{}".format(foldername, entry.name).encode("utf-8"))
	
	tarname = "{}.tar.z".format(foldername)
	
	cryptsab.tar_z_compress(tarname.encode("utf-8"), len(files_to_compress), *files_to_compress)

if __name__ == "__main__":
	for pagefolder in scandir(path.abspath(__file__ + "/../pages/")):
		filename, extension = path.splitext(pagefolder.name)
		if not pagefolder.is_dir():
			print(filename, " is not a folder.")
			continue
		searchDir(pagefolder)