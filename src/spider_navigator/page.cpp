#include "page.h"
#include <FL/fl_draw.H>
#include <stdexcept>

HTMLPage::HTMLPage(shared_ptr<HTMLNode> root, int x, int y, int w, int h) : Fl_Window(x, y, w, h) {
	this->root.swap(root);
	root.reset();
	end();
}

void HTMLPage::drawChildren(shared_ptr<HTMLNode> node) {
	for (auto child : node->children) {
		if (child->children.size() > 0) {
			drawChildren(child);
		}
	}
	if (node->data != nullptr) {
		fl_color(FL_FOREGROUND_COLOR);
		fl_draw(node->data, x(), y());
	}
}

void HTMLPage::draw() {
	if (root == nullptr) {
		throw std::logic_error("HTMLPage root not defined.");
	} else {
		drawChildren(root);
	}
}