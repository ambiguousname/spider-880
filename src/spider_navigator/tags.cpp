#include "tags.h"
#include <FL/fl_draw.H>
#include <typeinfo>

void HTMLNode::init() {
	return;
}

void HTMLNode::open(HTMLPage*, int&, int&) {
	return;
}

void HTMLNode::close(HTMLPage*) {
	return;
}

void HTMLNode::click(int, int, HTMLPage*) {
	return;
}

void HTMLNode::hover(int, int, HTMLPage* current_page) {
	current_page->parent_window->cursor(cursor);
}

void Text::open(HTMLPage* current_page, int& out_w, int& out_h) {
	out_w = current_page->w();
	out_h = 0;

	fl_font(FL_HELVETICA, 14);
	current_page->measure(_data.c_str(), out_w, out_h);
	fl_color(color);

	int cursor_x, cursor_y;
	current_page->getCursor(cursor_x, cursor_y);
	int height_buffer = current_page->getHeightBuffer();

	// TODO: Cut text up into chunks and wrap from that?
	if (cursor_x + out_w > current_page->w()) {
		cursor_x = current_page->x();
		cursor_y += height_buffer;
		height_buffer = 0;
	}
	fl_draw(_data.c_str(), cursor_x, cursor_y, out_w, out_h, FL_ALIGN_WRAP | FL_ALIGN_CENTER);
	cursor_x += out_w;

	height_buffer = out_h;
	// TODO: Is this hack okay? Does it not work with other displays?
	if (out_h > fl_size() + 2) {
		cursor_y += height_buffer;
		height_buffer = 0;
	}
	current_page->setHeightBuffer(height_buffer);
	current_page->setCursor(cursor_x, cursor_y);
}

void A::click(int, int, HTMLPage* current_page) {
	auto search = _attributes.find("href");
	if (search != _attributes.end()) {
		// TODO: Move on-click logic to python scripting.
		
		windowCreation constructor;
		if (current_page->parent_window->getLinkedWindow(search->second, constructor)) {
			auto window = constructor(current_page->x(), current_page->y(), current_page->parent_window->w(), current_page->parent_window->h());
			window->show();
		}
	}
}

void A::init() {
	for (auto c: _children) {
		if (typeid(*c).hash_code() == typeid(Text).hash_code()) {
			c->setColor(color);
		}
	}
}

void P::close(HTMLPage* current_page) {
	int cursor_x, cursor_y;
	current_page->getCursor(cursor_x, cursor_y);
	int height_buffer = current_page->getHeightBuffer();
	cursor_y += height_buffer + 20;
	height_buffer = 0;
	current_page->setCursor(current_page->x(), cursor_y);
	current_page->setHeightBuffer(height_buffer);
}

void Img::init() {
	auto src = _attributes.find("src");
	
	if (src != _attributes.end()) {
		// TODO: Fix.
		box = std::make_unique<ImageBox>(src->second.c_str());
	}
}

void Img::open(HTMLPage* current_page, int& out_w, int& out_h) {
	if (box == nullptr) {
		return;
	}
	int cursor_x, cursor_y;
	current_page->getCursor(cursor_x, cursor_y);
	int img_w = current_page->w() * 3/4;

	int img_x = 3 * (img_w - cursor_x)/16; 

	// TODO: `double` math?
	int full_w, full_h;
	box->getFullDimensions(full_w, full_h);
	double ratio = (double)full_h/(double)full_w;
	int img_h = ratio * img_w;

	box->prepareDraw(img_x, cursor_y, img_w, img_h);
	box->draw();

	cursor_y += img_h + 20;

	current_page->setCursor(cursor_x, cursor_y);
}