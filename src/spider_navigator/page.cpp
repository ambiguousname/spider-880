#include "page.h"
#include <FL/fl_draw.H>
#include <stdexcept>

HTMLWindow::HTMLWindow(shared_ptr<HTMLNode> root, int x, int y, int w, int h) : Fl_Window(x, y, w, h) {
	scrollbar = new Fl_Scroll(x, y, w, h);
	page = new HTMLPage(root, x, y, w - 20, h);
	scrollbar->end();
	resizable(this);
	end();
}

HTMLPage::HTMLPage(shared_ptr<HTMLNode> root, int x, int y, int w, int h) : Fl_Group(x, y, w, h) {
	this->root.swap(root);
	root.reset();
	end();
}

#include <iostream>
void HTMLPage::drawChildren() {
	// TODO: This is a queue.
	vector<shared_ptr<HTMLNode>> stack = {root};
	// TODO: To allow for showing when tags close, add it as a struct to the queue. You can use the std::variant type: https://en.cppreference.com/w/cpp/utility/variant
	// Either that or a struct holding either.

	int cursor_x = x();
	int cursor_y = y();
	rendered_nodes = {};
	while (stack.size() > 0) {
		shared_ptr<HTMLNode> node = stack.front();
		stack.erase(stack.begin());

		cout << node->tag;
		// TODO: Add a way to insert text nodes with navigator.py.
		if (node->tag == TEXT) {
			int text_width = w();
			int text_height = 0;

			fl_measure(node->data, text_width, text_height);
			fl_color(FL_FOREGROUND_COLOR);
			fl_draw(node->data, cursor_x, cursor_y, text_width, text_height, FL_ALIGN_WRAP | FL_ALIGN_CENTER);
			// cout << text_width << "," << text_height << endl;
			cursor_y += text_height + 20;
		}
		for (auto c : node->children) {
			stack.insert(stack.begin(), c);
		}
	}
	resize(x(), y(), this->parent()->w() - 20, cursor_y - y());
}

void HTMLPage::draw() {
	Fl_Group::draw();
	if (root == nullptr) {
		throw std::logic_error("HTMLPage root not defined.");
	} else {
		drawChildren();
	}
}

int HTMLPage::handle(int event) {
	if (Fl_Group::handle(event)) {
		return 1;
	}
	return 0;
}