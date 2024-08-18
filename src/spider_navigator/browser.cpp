#include "browser.hpp"
extern "C" {
	#include <cryptsab/crypt.h>
	#include <cryptsab/compress.h>
}
#include <FL/fl_ask.H>
#include <sys/stat.h>
#include <format>

void newWindow(std::string site, std::string filename) {
	OSSL_PROVIDER* pvdr;
	load_provider("legacy", &pvdr);

	unsigned char name[16];

	std::string name_pwd = std::format("WEBPAGE:{0}", site);

	derive_key_md4(name_pwd.c_str(), name);

	std::string file = std::format("{0}.tar.z.enc", (char*)name);

	struct stat st;
	int stat_result = stat(file.c_str(), &st);
	if (stat_result < 0) {
		fl_alert("Failed to read %s", file.c_str());
		unload_provider(pvdr);
		return;
	}

	unload_provider(pvdr);
}