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
	page = new HTMLPage(root, x, y, w - 20, h);
	scrollbar->end();
	resizable(this);
	end();
}

HTMLPage::HTMLPage(shared_ptr<HTMLNode> root, int x, int y, int w, int h) : Fl_Group(x, y, w, h), rendered_nodes() {
	this->root.swap(root);
	root.reset();
	end();
}

void HTMLPage::closeNode(vector<NodeQueueInfo>& queue, NodeQueueInfo info) {
	HTMLNodePtr node = info.node;
	// cursor_y += 20;
	if (node->tag == P) {
		cursor_y += height_buffer + 20;
		cursor_x = x();
		height_buffer = 0;
	}
}

void HTMLPage::openNode(vector<NodeQueueInfo>& queue, NodeQueueInfo info) {
	HTMLNodePtr node = info.node;
	if (node->tag == TEXT) {
		Fl_Color color = FL_FOREGROUND_COLOR;
		Fl_Cursor cursor = FL_CURSOR_INSERT;
		if (info.parent->tag == A) {
			color = FL_BLUE;
			cursor = FL_CURSOR_HAND;
		}

		int text_width = w();
		int text_height = 0;

		fl_measure(node->data, text_width, text_height);
		fl_color(color);
		// TODO: Cut text up into chunks and wrap from that?
		if (cursor_x + text_width > w()) {
			cursor_x = x();
			cursor_y += height_buffer;
			height_buffer = 0;
		}
		fl_draw(node->data, cursor_x, cursor_y, text_width, text_height, FL_ALIGN_WRAP | FL_ALIGN_CENTER);
		rendered_nodes.push_back({cursor_x, cursor_y, text_width, text_height, info, cursor});
		cursor_x += text_width;

		height_buffer = text_height;
		// TODO: Is this hack okay? Does it not work with other displays?
		if (text_height > fl_size() + 2) {
			cursor_y += height_buffer;
			height_buffer = 0;
		}
	}
}

void HTMLPage::drawChildren() {
	vector<NodeQueueInfo> queue = {{root, nullptr, OPEN_NODE}};

	cursor_x = x();
	cursor_y = y();
	height_buffer = 0;
	rendered_nodes = {};
	while (queue.size() > 0) {
		NodeQueueInfo node_info = queue.front();
		queue.erase(queue.begin());


		shared_ptr<HTMLNode> node = node_info.node;
		if (node_info.type == OPEN_NODE) {
			openNode(queue, node_info);
			queue.insert(queue.begin(), {node, node_info.parent, CLOSE_NODE});
			for (auto c : node->children) {
				queue.insert(queue.begin(), {c, node, OPEN_NODE});
			}
		} else if (node_info.type == CLOSE_NODE) {
			closeNode(queue, node_info);
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

bool HTMLPage::getRenderedFromPos(int x, int y, RenderedNode& out) {
	for (auto c : rendered_nodes) {
		if (x >= c.x && x <= c.x + c.w && y >= c.y && y <= c.y + c.h) {
			out = c;
			return true;
		}
	}
	return false;
}

int HTMLPage::hoverRendered() {
	HTMLWindow* parent = (HTMLWindow*)this->parent();

	int x = Fl::event_x();
	int y = Fl::event_y();
	RenderedNode rendered;
	if (getRenderedFromPos(x, y, rendered)) {
		parent->cursor(rendered.cursor);
		return 1;
	} else {
		parent->cursor(FL_CURSOR_DEFAULT);
		return 0;
	}
}

int HTMLPage::clickRendered() {
	int x = Fl::event_x();
	int y = Fl::event_y();
	RenderedNode rendered;
	if (getRenderedFromPos(x, y, rendered)) {
		if (rendered.node_info.node->tag == A) {
			auto attrs = rendered.node_info.node->attributes;
			auto search = attrs.find("href");
			if (search != attrs.begin()) {
				// TODO: Move on-click logic to python scripting.
				// 
			}
		}
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