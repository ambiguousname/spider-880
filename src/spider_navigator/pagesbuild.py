from ctypes import cdll, c_void_p, create_string_buffer, pointer, addressof
from os import path, scandir, remove
import argparse

cryptsab = None

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

base62 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

def searchDir(dir):
	files_to_compress = readFiles(dir)

	foldername, ext = path.splitext(dir.name)

	# Getting two keys, actually. One for our folder name, another for DES encryption. 

	full = create_string_buffer(16)
	cryptsab.derive_key_md4(foldername.encode("utf-8"), full)

	key, iv = full.value[:8], full.value[8:]

	name = create_string_buffer(16)
	cryptsab.derive_key_md4(f"WEPBAGE:{foldername}".encode("utf-8"), name)

	archive_name = ""
	for n in name.value:
		archive_name += base62[n % 62]

	tarname = f"{archive_name}.tar.z"
	
	cryptsab.tar_z_compress(tarname.encode("utf-8"), f"pages/".encode("utf-8"), len(files_to_compress), *files_to_compress)

	cryptsab.crypt_file_existing_cipher(1, key, iv, tarname.encode("utf-8"), f"{tarname}.enc".encode("utf-8"))

	remove(tarname)

	return f"{tarname}.enc".encode('utf-8')

if __name__ == "__main__":
	parser = argparse.ArgumentParser(
		prog="Pages Builder",
	)

	parser.add_argument("library_location")
	parser.add_argument("outfile")

	args = parser.parse_args()
	
	cryptsab = cdll.LoadLibrary(args.library_location)

	cryptsab.load_legacy_provider()
	cryptsab.start_cipher(b"des")

	tar_files = []
	for pagefolder in scandir(path.abspath(__file__ + "/../pages/")):
		filename, extension = path.splitext(pagefolder.name)
		if not pagefolder.is_dir():
			print(filename, " is not a folder.")
			continue
		tar_files.append(searchDir(pagefolder))
	
	out_page = args.outfile

	outname = path.splitext(out_page)

	cryptsab.tar_z_compress(f"{outname}.tar.z".encode("utf-8"), "".encode("utf-8"), len(tar_files), *tar_files)


	key_out = create_string_buffer(16)

	cryptsab.derive_key_md4(b"9973", key_out)

	key, iv = key_out[:8], key_out[8:]

	cryptsab.crypt_file_existing_cipher(1, key, iv, f"{outname}.tar.z".encode("utf-8"), out_page.encode("utf-8"))

	remove(f"{outname}.tar.z")

	cryptsab.end_cipher()
	cryptsab.unload_legacy_provider()

	for file in tar_files:
		remove(file)