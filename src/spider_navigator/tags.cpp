#include "tags.h"
#include <FL/fl_draw.H>

void HTMLNode::open(HTMLPage* current_page, int& out_w, int& out_h) {
	return;
}

void HTMLNode::close(HTMLPage* current_page) {
	return;
}

void HTMLNode::click(int x, int y, HTMLPage* current_page) {
	return;
}

void HTMLNode::hover(int x, int y, HTMLPage* current_page) {
	current_page->parent_window->cursor(cursor);
}

#include <iostream>
void Text::open(HTMLPage* current_page, int& out_w, int& out_h) {
	out_w = current_page->w();
	out_h = 0;

	fl_measure(_data.c_str(), out_w, out_h);
	fl_color(color);

	int cursor_x, cursor_y;
	current_page->getCursor(cursor_x, cursor_y);

	// TODO: Cut text up into chunks and wrap from that?
	if (cursor_x + out_w > current_page->w()) {
		cursor_x = current_page->x();
		// cursor_y += height_buffer;
		// height_buffer = 0;
	}
	fl_draw(_data.c_str(), cursor_x, cursor_y, out_h, out_h, FL_ALIGN_WRAP | FL_ALIGN_CENTER);
	cursor_x += out_w;

	// height_buffer = text_height;
	// TODO: Is this hack okay? Does it not work with other displays?
	if (out_h > fl_size() + 2) {
		// cursor_y += height_buffer;
		// height_buffer = 0;
	}
	current_page->setCursor(cursor_x, cursor_y);
}

void A::click(int x, int y, HTMLPage* current_page) {
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

void P::close(HTMLPage* current_page) {
	// cursor_y += height_buffer + 20;
	int cursor_x, cursor_y;
	current_page->getCursor(cursor_x, cursor_y);
	current_page->setCursor(current_page->x(), cursor_y);
	// height_buffer = 0;
}