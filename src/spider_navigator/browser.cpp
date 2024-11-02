#include "browser.hpp"
extern "C" {
	#include <cryptsab/crypt.h>
	#include <cryptsab/compress.h>
}
#include <FL/fl_ask.H>
#include <sys/stat.h>
#include <format>

OSSL_LIB_CTX* libctx;
OSSL_PROVIDER* pvdr;

void initializeBrowser() {
	libctx = lib_ctx_local_providers("./ossl-modules");
	load_provider_with_ctx("legacy", &pvdr, libctx);

	if (FILE* f = fopen("spider_navigator/pages.tar.z.enc", "r")) {
		fclose(f);
		EVP_CIPHER_CTX* des;
		if (start_des_cipher(libctx, &des) < 0) {
			fl_alert("Could not decrypt pages file. DES cipher could not be initialized.");
			return;
		}

		unsigned char pwd[16];
		
		if (derive_key_md4(libctx, "9973", pwd) < 0) {
			free_cipher(des);
			
			fl_alert("Could not decrypt pages file. MD4 key could not be derived.");
			return;
		}

		unsigned char key[8], iv[8];

		memcpy(key, pwd, 8);
		memcpy(iv, pwd + 8, 8);

		if (crypt_file(0, key, iv, "spider_navigator/pages.tar.z.enc", "spider_navigator/pages.tar.z", des) < 0) {
			free_cipher(des);

			fl_alert("Could not decrypt pages file. Decryption failed.");
			return;
		}

		free_cipher(des);

		if (tar_z_decompress("spider_navigator/pages.tar.z", "spider_navigator/") < 0) {
			fl_alert("Could not decompress pages file.");
			return;
		}

		remove("spider_navigator/pages.tar.z");
		remove("spider_navigator/pages.tar.z.enc");
	}
}

void uninitializeBrowser() {
	unload_provider(pvdr);
	free_lib_ctx(libctx);
}

const char* base62 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

std::string filenameFromHash(unsigned char name[16]) {
	std::string filename;
	for (size_t i = 0; i < 16; i++) {
		unsigned int v = name[i];
		filename.push_back(base62[v % 62]);
	}
	return filename;
}

void newWindow(std::string site, std::string foldername) {
	unsigned char name[16];

	std::string name_pwd = std::format("WEBPAGE:{0}", site);

	if (derive_key_md4(libctx, name_pwd.c_str(), name) < 0) {
		fl_alert("Could not derive MD4 hash from %s", site.c_str());
		return;
	} 


	std::string filename = filenameFromHash(name);
	std::string file = std::format("spider_navigator/{0}.tar.z.enc", filename);

	struct stat st;
	int stat_result = stat(file.c_str(), &st);
	if (stat_result < 0) {
		fl_alert("Failed to read %s", file.c_str());
		return;
	}

	unsigned char pwd[16];

	if (derive_key_md4(libctx, site.c_str(), pwd) < 0) {
		fl_alert("Could not derive MD4 password from %s", site.c_str());
		return;
	}

	unsigned char key[8], iv[8];
	for (int i = 0; i < 16; i++) {
		if (i < 8) {
			key[i] = pwd[i];
		} else {
			iv[i % 8] = pwd[i];
		}
	}

	EVP_CIPHER_CTX* des;
	if (start_des_cipher(libctx, &des) < 0) {
		fl_alert("Could not decrypt %s. DES cipher could not be initialized.", file.c_str());
		return;
	}

	std::string decrypted_file = std::format("spider_navigator/{0}.tar.z", filename);

	if (crypt_file(0, key, iv, file.c_str(), decrypted_file.c_str(), des) < 0) {
		free_cipher(des);
		fl_alert("Could not decrypt %s. Decryption failed.", file.c_str());
		return;
	}

	free_cipher(des);

	if (tar_z_decompress(decrypted_file.c_str(), std::format("spider_navigator/{0}", "./").c_str()) < 0) {
		fl_alert("Could not decompress %s.", decrypted_file.c_str());
		return;
	}

	remove(decrypted_file.c_str());
	remove(file.c_str());
}