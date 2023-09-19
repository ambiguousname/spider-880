#include "page.h"
#include <FL/fl_draw.H>
#include <stdexcept>
#include <string>

HTMLPage::HTMLPage(shared_ptr<HTMLNode> root, int x, int y, int w, int h) : Fl_Window(x, y, w, h) {
	this->root.swap(root);
	root.reset();
	resizable(this);
	end();
}

#include <iostream>
void HTMLPage::drawChildren() {
	vector<shared_ptr<HTMLNode>> stack = {root};

	int cursor_x = 0;
	int cursor_y = 20;
	while (stack.size() > 0) {
		shared_ptr<HTMLNode> node = stack.back();
		stack.pop_back();

		for (auto c : node->children) {
			stack.push_back(c);
			if (c->tag == NodeType::P) {
				int text_width = w();
				int text_height = 0;
				fl_measure(c->data, text_width, text_height);
				fl_color(FL_FOREGROUND_COLOR);
				fl_draw(c->data, cursor_x, cursor_y, text_width, text_height, FL_ALIGN_WRAP | FL_ALIGN_CENTER);
				// cout << text_width << "," << text_height << endl;
				cursor_y += text_height + 20;
			}
		}
	}
}

void HTMLPage::draw() {
	Fl_Window::draw();
	if (root == nullptr) {
		throw std::logic_error("HTMLPage root not defined.");
	} else {
		drawChildren();
	}
}