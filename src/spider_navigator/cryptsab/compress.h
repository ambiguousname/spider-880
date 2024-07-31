#pragma once

int tar_z_compress(const char* compressed_path, int num_files, ...);
int tar_z_decompress(const char* compressed_path);