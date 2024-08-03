from ctypes import cdll, c_size_t, create_string_buffer
from os import path, scandir, remove
from sys import argv

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
	
	# cryptsab.tar_z_compress(argv[1].encode("utf-8"), len(tar_files), *tar_files)

	# for file in tar_files:
	# 	remove(file)