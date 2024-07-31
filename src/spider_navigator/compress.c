#include <archive.h>
#include <archive_entry.h>
#include <stdio.h>
#include <stdarg.h>

#define ERROR(archive, e) fprintf(stderr, "%s: %s\n", e, archive_error_string(archive));

int tar_z_compress(const char* compressed_path, int num_files, ...) {
	struct archive* a;
	
	a = archive_write_new();
	archive_write_add_filter_compress(a);
	archive_write_set_format_pax_restricted(a);
	int open_result = archive_write_open_filename(a, compressed_path);
	if (open_result == ARCHIVE_FATAL) {
		ERROR(a, "Could not open file");
		return -1;
	}

	struct stat st;
	struct archive_entry* entry = archive_entry_new();

	int inlen;
	FILE* infile;
	unsigned char buff[8192];

	va_list paths;
	va_start(paths, num_files);
	for (int i = 0; i < num_files; i++) {
		const char* filename = va_arg(paths, const char*);
		int stat_result = stat(filename, &st);
		if (stat_result < 0) {
			fprintf(stderr, "Error, could not get metadata for %s: %i", filename, errno);
			return -1;
		}

		archive_entry_set_pathname(entry, filename);
		archive_entry_set_size(entry, st.st_size);
		archive_entry_set_filetype(entry, AE_IFREG);
		archive_entry_set_perm(entry, 0644);
		if (archive_write_header(a, entry) != ARCHIVE_OK) {
			ERROR(a, "Could not write header");
			return -1;
		}

		infile = fopen(filename, "rb");
		if (infile == NULL) {
			fprintf("Could not read %s: %i", filename, errno);
			return -1;
		}

		do {
			inlen = fread(buff, 1, sizeof(buff), infile);
			if (archive_write_data(a, buff, inlen) < 0) {
				ERROR(a, "Could not write data");
				return -1;
			}
		} while (inlen > 0);
		fclose(infile);
		
		entry = archive_entry_clear(entry);
	}
	va_end(paths);
	
	archive_entry_free(entry);

	archive_write_close(a);
	archive_write_free(a);

	return 1;
}

int tar_z_decompress(const char* compressed_path, const char* decompressed_path) {
	struct archive* a;

	a = archive_read_new();
	archive_read_support_filter_compress(a);
	archive_read_support_format_tar(a);

	struct stat* st;
	int stat_result = stat(compressed_path, st);
	if (stat_result < 0) {
		fprintf(stderr, "Error, could not get metadata for %s: %i", compressed_path, errno);
		return -1;
	}

	int read_result = archive_read_open_filename(a, compressed_path, st->st_blksize);
	if (read_result != ARCHIVE_OK) {
		ERROR(a, "Could not read archive");
		return -1;
	}

	struct archive* ext;
	int flags;
	flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;

	ext = archive_write_disk_new();
	archive_write_disk_set_options(ext, flags);
	archive_write_disk_set_standard_lookup(ext);

	
	struct archive_entry *entry;
	for(;;) {
		int header_read = archive_read_next_header2(a, &entry);
		if (header_read == ARCHIVE_EOF) {
			break;
		}
		if (header_read < ARCHIVE_OK) {
			ERROR(a, "Could not read header");
			return -1;
		}
		
		int header_write = archive_write_header(ext, entry);
		if (header_write < ARCHIVE_OK) {
			ERROR(a, "Could not write header");
			return -1;
		} else if (archive_entry_size(entry) > 0) {
			// TODO:
		}
	}
	// TODO:
	return 1;
}


int main() {
	if (tar_z_compress("tags.tar.z", 2, "tags.h", "page.h") > 0) {
		return 0;
	} else {
		return -1;
	}
}