#include "tags.h"
#include "page.h"
#include <FL/fl_draw.H>

void HTMLNode::hover(int x, int y, std::unique_ptr<HTMLPage> current_page) {
	current_page->parent_window->cursor(cursor);
}

void Text::open(std::unique_ptr<HTMLPage> current_page) {
	int text_width = current_page->w();
	int text_height = 0;

	fl_measure(data.c_str(), text_width, text_height);
	fl_color(color);

	int cursor_x, cursor_y;
	current_page->getCursor(cursor_x, cursor_y);

	// TODO: Cut text up into chunks and wrap from that?
	if (cursor_x + text_width > current_page->w()) {
		cursor_x = current_page->x();
		// cursor_y += height_buffer;
		// height_buffer = 0;
	}
	fl_draw(data.c_str(), cursor_x, cursor_y, text_width, text_height, FL_ALIGN_WRAP | FL_ALIGN_CENTER);
	cursor_x += text_width;

	// height_buffer = text_height;
	// TODO: Is this hack okay? Does it not work with other displays?
	if (text_height > fl_size() + 2) {
		// cursor_y += height_buffer;
		// height_buffer = 0;
	}
	current_page->setCursor(cursor_x, cursor_y);
}

void A::click(int x, int y, std::unique_ptr<HTMLPage> current_page) {
	auto search = attributes.find("href");
	if (search != attributes.end()) {
		// TODO: Move on-click logic to python scripting.
		
		windowCreation constructor;
		if (current_page->parent_window->getLinkedWindow(search->second, constructor)) {
			auto window = constructor(current_page->x(), current_page->y(), current_page->parent_window->w(), current_page->parent_window->h());
			window->show();
		}
	}
}

void P::close(std::unique_ptr<HTMLPage> current_page) {
	// cursor_y += height_buffer + 20;
	int cursor_x, cursor_y;
	current_page->getCursor(cursor_x, cursor_y);
	current_page->setCursor(current_page->x(), cursor_y);
	// height_buffer = 0;
}