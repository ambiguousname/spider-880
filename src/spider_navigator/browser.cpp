#include "browser.hpp"
extern "C" {
	#include <cryptsab/crypt.h>
	#include <cryptsab/compress.h>
}
#include <FL/fl_ask.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Input.H>
#include <sys/stat.h>
#include <format>
#include <util/base_sounds.hpp>

void aboutCallback(Fl_Widget*, void*) {
	errorSound();
	fl_alert("Bureau of Sabotage Network Navigator\nBy Brian Gertwig");
}

void showHelp(Fl_Widget*, void* w) {
	BrowserWindow* window = (BrowserWindow*)w;
	newWindow("gertwig_blog", "index.html", window->x() + 10, window->y() + 10, window->w(), window->h());
}

BrowserWindow::BrowserWindow(std::string filepath, int x, int y, int w, int h) : Fl_Window(x, y, w, h), menu_bar(0, 0, w, 20) {
	menu_bar.add("NavSab", 0, 0, 0, FL_MENU_INACTIVE);
	menu_bar.add("Help/About", FL_CTRL+'a', aboutCallback);
	menu_bar.add("Help/Website", FL_CTRL+'w', showHelp, this);

	try {
		xmlpp::DomParser parser(filepath);
		xmlpp::Document* d = parser.get_document();
		xmlpp::Element* root = d->get_root_node();

		xmlpp::Node::NodeList children = root->get_children();
		for (auto child : children) {
			Glib::ustring child_name = child->get_name();

			if (child_name == "head") {
				evaluateHead(dynamic_cast<xmlpp::Element*>(child));
			} else if (child_name == "body") {
				scrollbar = new Fl_Scroll(0, 25, w, h - 25);
				body = new Body(std::shared_ptr<Fl_Window>(this), dynamic_cast<xmlpp::Element*>(child), 0, 20, w, h - 20);
				scrollbar->end();
				scrollbar->type(Fl_Scroll::VERTICAL);
			}
		}
	} catch (xmlpp::parse_error& e) {
		fl_alert("Could not parse: %s", e.what());
	}
	
	resizable(this);
	end();
}

void BrowserWindow::draw() {
	body->resize(body->x(), body->y(), w(), body->h());
	Fl_Window::draw();
}

void BrowserWindow::evaluateHead(xmlpp::Element* head) {
	if (head != nullptr) {
		xmlpp::Node::NodeList children = head->get_children();
		for (auto child : children) {
			Glib::ustring child_name = child->get_name();

			if (child_name == "title") {
				if (auto t = dynamic_cast<xmlpp::TextNode*>(child->get_first_child())) {
					title = t->get_content();
					label(title.c_str());	
				}
			}
		}
	}
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

const char* base16 = "0123456789abcdef";

std::string filenameFromHash(unsigned char name[16]) {
	std::string filename;
	for (size_t i = 0; i < 16; i++) {
		unsigned char v = name[i];
		filename.push_back(base16[(v >> 4) % 16]);
		filename.push_back(base16[(v & 0xff) % 16]);
	}
	return filename;
}

void browserFromFile(std::string filepath, int x, int y, int w, int h) {
	BrowserWindow* window = new BrowserWindow(filepath, x, y, w, h);
	window->show();
}

void decryptAccess(std::string filepath, int x, int y, int w, int h) {
	Fl_Window* window = new Fl_Window(x, y, w, h, filepath.c_str());

	std::string label = std::format("The file {0} is encrypted. Please enter a password:", filepath);
	Fl_Box* box = new Fl_Box(FL_DOWN_BOX, 0, h/2, w, h/4, 0);
	box->copy_label(label.c_str());
	box->align(FL_ALIGN_TOP | FL_ALIGN_WRAP);

	Fl_Input* input = new Fl_Input(0, h/2, w, 20);

	Fl_Return_Button* btn = new Fl_Return_Button(0, h/2 + 20, w/4, 20, "Enter");

	window->end();
	
	window->resizable(window);

	window->show();
}

void newWindow(std::string site, std::string html_file, int x, int y, int w, int h) {
	std::string file_loc = std::format("spider_navigator/{0}/{1}", site, html_file);
	if (access(file_loc.c_str(), F_OK) == 0) {
		browserFromFile(file_loc, x, y, w, h);
		return;
	}

	std::string encrypted_file_loc = std::format("{0}.enc", file_loc);
	if (access(encrypted_file_loc.c_str(), F_OK) == 0) {
		decryptAccess(encrypted_file_loc, x, y, w, h);
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

	if (access(file.c_str(), F_OK) == -1) {
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

	if (access(file_loc.c_str(), F_OK) == 0) {
		browserFromFile(file_loc, x, y, w, h);
	} else if (access(encrypted_file_loc.c_str(), F_OK) == 0) {
		decryptAccess(encrypted_file_loc, x, y, w, h);
	} else {
		fl_alert("No such file %s exists.", file_loc.c_str());
	}
}