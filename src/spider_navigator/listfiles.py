from os import scandir, path

root = path.abspath(__file__ + "/../pages/")

def searchDir(dir):
	files = []
	for entry in scandir(dir):
		filename, extension = path.splitext(entry.name)
		if entry.is_dir():
			searchDir(entry)
		elif extension == ".cpphtml":
			entry_path = path.abspath(entry.path)
			base, full_filename = path.split(entry_path)
			pth = path.join(base, filename + ".cpp")
			
			f = open(path.join(root, "../list.txt"), "a")
			f.write(pth + "\n")
			f.close()

			files.append(entry.path)
	if len(files) > 0:
		print('DIR:')
		for file in files:
			print(path.abspath(file))
		
if __name__ == "__main__":
	f = open(path.join(root, "../list.txt"), "w")
	f.truncate()
	f.close()
	searchDir(root)