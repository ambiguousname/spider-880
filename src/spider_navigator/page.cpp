#include "page.hpp"
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <stdexcept>
#include <libxml++/libxml++.h>

HTMLPage::HTMLPage(xmlpp::Element* body_root, BrowserWindow* const parent, int x, int y, int w, int h, int horizontal_padding) : Fl_Group(x, y, w, h), padding(horizontal_padding), parent_window(parent) {
	if (body_root != nullptr) {
		parseElement(body_root);
	} else {
		fl_alert("Could not ready <body> tag.");
	}
	end();
}

void HTMLPage::parseElement(xmlpp::Element* element) {
	for (auto child : element->get_children()) {

	}	
}