#pragma once

/// @brief Compress a series of files.
/// @param compressed_path Where to store the new archive.
/// @param files_location The relative path where these files are stored from where the program is executing. This will be exlcuded from the archive.
/// @param num_files Number of files to compress.
/// @param ... const char* list of file paths. Any folder names included here will be preserved in the archive.
/// @return ARCHIVE_OK on success, an int < 0 on failure.
int tar_z_compress(const char* compressed_path, const char* files_location, int num_files, ...);
int tar_z_decompress(const char* compressed_path, const char* decompress_path);