#include "page.h"
#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <stdexcept>
#include <variant>

HTMLWindow::HTMLWindow(shared_ptr<HTMLNode> root, int x, int y, int w, int h) : Fl_Window(x, y, w, h) {
	auto find_title = root->attributes.find("title");
	if (find_title != root->attributes.end()) {
		label(find_title->second.c_str());
	}
	scrollbar = new Fl_Scroll(x, y, w, h);
	page = new HTMLPage(root, make_shared<HTMLWindow>(this), x, y, w - 20, h);
	scrollbar->end();

	resizable(this);
	end();
}

bool HTMLWindow::getLinkedWindow(string name, windowCreation& out) {
	auto search = linked_windows.find(name);
	if (search != linked_windows.end()) {
		out = search->second;
		return true;
	}
	return false;
}

HTMLPage::HTMLPage(shared_ptr<HTMLNode> root, shared_ptr<HTMLWindow> parent, int x, int y, int w, int h) : Fl_Group(x, y, w, h), parent_window(parent), interactive_nodes() {
	this->root.swap(root);
	root.reset();
	initNode(root);
	end();
}

void HTMLPage::initNode(HTMLNodePtr node) {
	if (node->interactive) {
		interactive_nodes.push_back(node);
	}
	for (auto c : node->children) {
		c->setParent(node);
		initNode(node);
	}
}

void HTMLPage::drawChildren() {
	vector<NodeQueueInfo> queue = {{root, OPEN_NODE}};

	cursor_x = x();
	cursor_y = y();
	height_buffer = 0;
	while (queue.size() > 0) {
		NodeQueueInfo node_info = queue.front();
		queue.erase(queue.begin());

		shared_ptr<HTMLNode> node = node_info.node;
		if (node_info.type == OPEN_NODE) {
			node_info.node->open(cursor_x, cursor_y);
			queue.insert(queue.begin(), {node, CLOSE_NODE});
			for (auto c : node->children) {
				queue.insert(queue.begin(), {c, OPEN_NODE});
			}
		} else if (node_info.type == CLOSE_NODE) {
			node_info.node->close();
		}
	}
	// cout << "-----" << endl;
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

bool HTMLPage::getInteractiveFromPos(int x, int y, HTMLNodePtr out) {
	for (auto c : interactive_nodes) {
		if (x >= c.x && x <= c.x + c.w && y >= c.y && y <= c.y + c.h) {
			out = c;
			return true;
		}
	}
	return false;
}

int HTMLPage::hoverRendered() {

	int x = Fl::event_x();
	int y = Fl::event_y();
	HTMLNodePtr rendered;
	if (getInteractiveFromPos(x, y, rendered)) {
		rendered->hover(x, y, this);
		return 1;
	} else {
		parent_window->cursor(FL_CURSOR_DEFAULT);
		return 0;
	}
}

int HTMLPage::clickRendered() {
	int x = Fl::event_x();
	int y = Fl::event_y();
	HTMLNodePtr rendered;
	if (getInteractiveFromPos(x, y, rendered)) {
		rendered->click();
		return 1;
	} else {
		return 0;
	}
}

int HTMLPage::handle(int event) {
	if (event == FL_ENTER || event == FL_MOVE) {
		if (hoverRendered()) {
			return 1;
		}
	}
	if (event == FL_PUSH) {
		if (clickRendered()) {
			return 1;
		}
	}
	if (Fl_Group::handle(event)) {
		return 1;
	}

	return 0;
}