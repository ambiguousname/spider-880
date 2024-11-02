#include "browser.hpp"
extern "C" {
	#include <cryptsab/crypt.h>
	#include <cryptsab/compress.h>
}
#include <FL/fl_ask.H>
#include <sys/stat.h>
#include <format>
#include <util/base_sounds.hpp>

void aboutCallback(Fl_Widget*, void*) {
	// fl_message_icon();
	errorSound();
	fl_alert("Bureau of Sabotage Network Navigator\nBy Brian Gertwig");
}


void showHelp(Fl_Widget* widget, void*) {
	BrowserWindow* window = dynamic_cast<BrowserWindow*>(widget);
	newWindow("gertwig_blog", "index.html", window->x() + 10, window->y() + 10, window->w(), window->h());
}

BrowserWindow::BrowserWindow(std::string filepath, int x, int y, int w, int h) : Fl_Window(x, y, w, h), menu_bar(0, 0, w, 20) {
	menu_bar.add("NavSab", 0, 0, 0, FL_MENU_INACTIVE);
	menu_bar.add("Help/About", FL_CTRL+'a', aboutCallback);
	menu_bar.add("Help/Website", FL_CTRL+'w', showHelp);

	// auto attributes = root->attributes();
	// auto find_title = attributes.find("title");
	// if (find_title != attributes.end()) {
	// 	// Create a constant reference to the title so c_str doesn't bug out:
	// 	title = find_title->second;
	// 	label(title.c_str());
	// }

	scrollbar = new Fl_Scroll(0, 25, w, h - 25);

	xmlpp::DomParser parser(filepath);
	xmlpp::Document* d = parser.get_document();
	xmlpp::Element* root = d->get_root_node();

	xmlpp::Node::NodeList children = root->get_children();
	for (auto child : children) {
		Glib::ustring child_name = child->get_name();

		if (child_name == "head") {

		} else if (child_name == "body") {
			body = new Body(dynamic_cast<xmlpp::Element*>(child), 0, 25, w, h - 25);
		}
	}
	scrollbar->end();
	scrollbar->type(Fl_Scroll::VERTICAL);
}



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

void browserFromFile(std::string filepath, int x, int y, int w, int h) {
	BrowserWindow* window = new BrowserWindow(filepath, x, y, w, h);
	window->end();
	window->resizable(window);
	window->show();
}

void newWindow(std::string site, std::string html_file, int x, int y, int w, int h) {
	std::string file_loc = std::format("spider_navigator/{0}/{1}", site, html_file);
	if (access(file_loc.c_str(), F_OK) != -1) {
		browserFromFile(file_loc, x, y, w, h);
		return;
	}

	unsigned char name[16];

	std::string name_pwd = std::format("WEBPAGE:{0}", site);

	if (derive_key_md4(libctx, name_pwd.c_str(), name) < 0) {
		fl_alert("Could not derive MD4 hash from %s", site.c_str());
		return;
	} 


	std::string filename = filenameFromHash(name);
	std::string file = std::format("spider_navigator/{0}.tar.z.enc", filename);

	if (access(file.c_str(), F_OK) != -1) {
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

	browserFromFile(file_loc, x, y, w, h);
}