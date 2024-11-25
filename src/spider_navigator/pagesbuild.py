from ctypes import cdll, c_void_p, create_string_buffer, pointer, addressof
from os import path, scandir, remove
import argparse
import tomllib

cryptsab = None

def encryptSingleFile(dir, file):
	full = create_string_buffer(16)
	cryptsab.derive_key_md4(None, file['pwd'].encode("utf-8"), full)

	key, iv = full.raw[:8], full.raw[8:]

	filepath = path.join(dir, file['file'])

	p = f"{filepath}.enc".encode("utf-8")

	cryptsab.crypt_file_existing_cipher(1, key, iv, filepath.encode("utf-8"), p)

	return p, f"{file['file']}.enc"

def readFiles(dir, relative_path=""):
	foldername, ext = path.splitext(dir.name)

	ignore_files = []
	files = []
	files_to_remove = []

	file_info_path = path.join(dir, "files.toml")
	if path.exists(file_info_path):
		with open(file_info_path, "rb") as f:
			file_info = tomllib.load(f)
			for value in file_info.values():
				ignore_files.append(value['file'])

				filepath, name = encryptSingleFile(dir, value)
				files.append(f"{relative_path}{foldername}/{name}".encode("utf-8"))
				files_to_remove.append(filepath)

	for entry in scandir(dir):
		if entry.is_dir():
			new_files, new_remove = readFiles(entry, f"{foldername}/")

			files = files + new_files
			files_to_remove = files_to_remove + new_remove
		
		filename, extension = path.splitext(entry.name)

		if extension == ".html" and entry.name not in ignore_files:
			files.append(f"{relative_path}{foldername}/{entry.name}".encode("utf-8"))
	return files, files_to_remove

def searchDir(dir):
	files_to_compress, files_to_remove = readFiles(dir)

	foldername, ext = path.splitext(dir.name)

	# Getting two keys, actually. One for our folder name, another for DES encryption. 

	full = create_string_buffer(16)
	cryptsab.derive_key_md4(None, foldername.encode("utf-8"), full)

	key, iv = full.raw[:8], full.raw[8:]

	name = create_string_buffer(16)
	cryptsab.derive_key_md4(None, f"WEBPAGE:{foldername}".encode("utf-8"), name)

	archive_name = name.raw.hex()

	tarname = f"{archive_name}.tar.z"
	
	cryptsab.tar_z_compress(tarname.encode("utf-8"), path.abspath(__file__ + "/../pages/").encode("utf-8"), len(files_to_compress), *files_to_compress)

	cryptsab.crypt_file_existing_cipher(1, key, iv, tarname.encode("utf-8"), f"{tarname}.enc".encode("utf-8"))

	remove(tarname)

	for f in files_to_remove:
		remove(f)

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

	outname, ext = path.splitext(out_page)

	cryptsab.tar_z_compress(f"{outname}.tar.z".encode("utf-8"), ".".encode("utf-8"), len(tar_files), *tar_files)


	key_out = create_string_buffer(16)

	cryptsab.derive_key_md4(None, b"9973", key_out)

	key, iv = key_out[:8], key_out[8:]

	cryptsab.crypt_file_existing_cipher(1, key, iv, f"{outname}.tar.z".encode("utf-8"), out_page.encode("utf-8"))

	remove(f"{outname}.tar.z")

	cryptsab.end_cipher()
	cryptsab.unload_legacy_provider()

	for file in tar_files:
		remove(file)