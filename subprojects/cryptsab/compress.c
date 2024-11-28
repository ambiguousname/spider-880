#include "include/cryptsab/compress.h"
#include <archive.h>
#include <archive_entry.h>
#include <stdio.h>
#include <stdarg.h>

#include <string.h>
#include <errno.h>
#include <stddef.h>

#define ERR(archive, e) fprintf(stderr, "%s: %s\n", e, archive_error_string(archive));

int copy_archive(struct archive* a, struct archive* b) {
	const void* buff;
	size_t len;
	la_int64_t offset;

	for (;;) {
		int read_out = archive_read_data_block(a, &buff, &len, &offset);
		if (read_out == ARCHIVE_EOF) {
			return ARCHIVE_OK;
		}
		if (read_out < ARCHIVE_OK) {
			return read_out;
		}
		int write = archive_write_data_block(b, buff, len, offset);
		if (write < ARCHIVE_OK) {
			return write;
		}
	}
}

#define ARCHIVE_FREE(a, type, errno) if (errno != ARCHIVE_FATAL) { archive_ ##type## _close(a); } archive_ ##type## _free(a);

int tar_z_compress(const char* compressed_path, const char* files_location, int num_files, ...) {
	struct archive* a;

	int files_location_len = strlen(files_location);
	
	a = archive_write_new();
	archive_write_add_filter_compress(a);
	archive_write_set_format_pax_restricted(a);

	int open_result = archive_write_open_filename(a, compressed_path);
	if (open_result == ARCHIVE_FATAL) {
		ERR(a, "Could not open file");
		return open_result;
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

		int file_len = strlen(filename);

		char file_local_location[files_location_len + file_len];

		sprintf(file_local_location, "%s/%s", files_location, filename);

		int stat_result = stat(file_local_location, &st);
		if (stat_result < 0) {
			fprintf(stderr, "Error, could not get metadata for %s: %i\n", file_local_location, errno);
			archive_entry_free(entry);
			ARCHIVE_FREE(a, write, ARCHIVE_FAILED);
			return ARCHIVE_FAILED;
		}

		archive_entry_set_pathname(entry, filename);
		archive_entry_set_size(entry, st.st_size);
		archive_entry_set_atime(entry, st.st_atime, 0);
		archive_entry_set_mtime(entry, st.st_mtime, 0);
		archive_entry_set_ctime(entry, st.st_ctime, 0);
		archive_entry_set_filetype(entry, AE_IFREG);
		archive_entry_set_perm(entry, 0644);

		int header_write = archive_write_header(a, entry);
		if (header_write < ARCHIVE_OK) {
			ERR(a, "Could not write header");

			archive_entry_free(entry);
			ARCHIVE_FREE(a, write, header_write);

			return header_write;
		}

		infile = fopen(file_local_location, "rb");
		if (infile == NULL) {
			fprintf(stderr, "Could not read %s: %i", filename, errno);

			archive_entry_free(entry);
			ARCHIVE_FREE(a, write, ARCHIVE_FAILED);

			return ARCHIVE_FAILED;
		}

		do {
			inlen = fread(buff, 1, sizeof(buff), infile);
			int write_result = archive_write_data(a, buff, inlen);
			if (write_result < ARCHIVE_OK) {
				ERR(a, "Could not write data");

				archive_entry_free(entry);
				ARCHIVE_FREE(a, write, write_result);

				return write_result;
			}
		} while (inlen > 0);
		fclose(infile);

		int finish = archive_write_finish_entry(a);
		if (finish < ARCHIVE_OK) {
			ERR(a, "Could not finish write");

			archive_entry_free(entry);
			ARCHIVE_FREE(a, write, finish);

			return finish;
		}
		
		entry = archive_entry_clear(entry);
	}
	va_end(paths);
	
	archive_entry_free(entry);

	archive_write_close(a);
	archive_write_free(a);

	return ARCHIVE_OK;
}

int tar_z_decompress(const char* compressed_path, const char* decompress_path) {
	struct archive* a;

	a = archive_read_new();
	archive_read_support_filter_compress(a);
	archive_read_support_format_tar(a);

	struct stat st;
	int stat_result = stat(compressed_path, &st);
	if (stat_result < 0) {
		fprintf(stderr, "Error, could not get metadata for %s: %i", compressed_path, errno);

		ARCHIVE_FREE(a, read, ARCHIVE_FAILED);

		return ARCHIVE_FAILED;
	}

	int read_result = archive_read_open_filename(a, compressed_path, st.st_size);
	if (read_result < ARCHIVE_OK) {
		ERR(a, "Could not read archive");

		ARCHIVE_FREE(a, read, read_result);

		return read_result;
	}

	struct archive* ext;
	int flags;
	flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;

	ext = archive_write_disk_new();
	archive_write_disk_set_options(ext, flags);
	archive_write_disk_set_standard_lookup(ext);

	
	struct archive_entry *entry;
	for(;;) {
		int header_read = archive_read_next_header(a, &entry);
		if (header_read == ARCHIVE_EOF) {
			break;
		}
		if (header_read < ARCHIVE_OK) {
			ERR(ext, "Could not read header");

			ARCHIVE_FREE(a, read, header_read);
			ARCHIVE_FREE(ext, write, ARCHIVE_FAILED);
			archive_entry_free(entry);

			return header_read;
		}


		const char* path = archive_entry_pathname(entry);
		int new_pathlen = snprintf(NULL, 0, "%s%s", decompress_path, path);
		char new_path[new_pathlen + 1];
		snprintf(new_path, sizeof new_path, "%s%s", decompress_path, path);
		archive_entry_set_pathname(entry, new_path);
		
		int header_write = archive_write_header(ext, entry);
		if (header_write < ARCHIVE_OK) {
			ERR(ext, "Could not write header");

			ARCHIVE_FREE(ext, write, header_write);
			ARCHIVE_FREE(a, read, ARCHIVE_FAILED);

			return header_write;
		} else if (archive_entry_size(entry) > 0) {
			int copy = copy_archive(a, ext);
			if (copy < ARCHIVE_OK) {
				ERR(ext, "Could not copy data");

				ARCHIVE_FREE(ext, write, copy);
				ARCHIVE_FREE(a, read, copy);

				return copy;
			}
		}

		int finish = archive_write_finish_entry(ext);
		if (finish < ARCHIVE_OK) {
			ERR(ext, "Could not finish write");

			ARCHIVE_FREE(ext, write, finish);
			ARCHIVE_FREE(a, read, ARCHIVE_FAILED);

			return finish;
		}
	}
	
	archive_read_close(a);
	archive_read_free(a);
	archive_write_close(ext);
	archive_write_free(ext);

	return ARCHIVE_OK;
}