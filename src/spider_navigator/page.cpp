#include "page.hpp"
#include "browser.hpp"
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <stdexcept>
#include <util/base_sounds.hpp>

void aboutCallback(Fl_Widget*, void*) {
	// fl_message_icon();
	errorSound();
	fl_alert("Bureau of Sabotage Network Navigator\nBy Brian Gertwig");
}

typedef HTMLWindow* (*page_create)(int, int, int, int);

void showHelp(Fl_Widget*, void*) {
	newWindow("gertwig_blog", "index.html");
}

HTMLWindow::HTMLWindow(std::shared_ptr<HTMLNode> root, int x, int y, int w, int h) : Fl_Window(x, y, w, h), menu_bar(0, 0, w, 20) {
	menu_bar.add("NavSab", 0, 0, 0, FL_MENU_INACTIVE);
	menu_bar.add("Help/About", FL_CTRL+'a', aboutCallback);
	menu_bar.add("Help/Website", FL_CTRL+'w', showHelp);

	auto attributes = root->attributes();
	auto find_title = attributes.find("title");
	if (find_title != attributes.end()) {
		// Create a constant reference to the title so c_str doesn't bug out:
		title = find_title->second;
		label(title.c_str());
	}

	scrollbar = new Fl_Scroll(0, 25, w, h - 25);
	page = new HTMLPage(root, std::shared_ptr<HTMLWindow>(this), 0, 25, w, h - 25, 10);
	scrollbar->end();
	scrollbar->type(Fl_Scroll::VERTICAL);

	resizable(this);
}

HTMLPage::HTMLPage(std::shared_ptr<HTMLNode> r, std::shared_ptr<HTMLWindow> parent, int x, int y, int w, int h, int horizontal_padding) : Fl_Group(x, y, w, h), padding(horizontal_padding), interactive_nodes(), parent_window(parent) {
	root.swap(r);
	r.reset();
	initNode(root);
	end();
}

void HTMLPage::initNode(HTMLNodePtr node) {
	node->init();
	for (auto c : node->children()) {
		c->setParent(node);
		initNode(c);
	}
}

#pragma region drawHTML

void HTMLPage::measureChildren(std::vector<std::unique_ptr<NodeStackInfo>>& stack, std::vector<std::unique_ptr<NodeStackInfo>>& drawStack) {
	interactive_nodes.clear();

	cursor_x = x();
	cursor_y = y();
	while (stack.size() > 0) {
		std::unique_ptr<NodeStackInfo> node_info = move(stack.front());
		stack.erase(stack.begin());

		std::shared_ptr<HTMLNode> node = node_info->node;
		if (node_info->type == OPEN_NODE) {

			int out_w, out_h, start_x, start_y;
			out_w = 0;
			out_h = 0;
			start_x = cursor_x;
			start_y = cursor_y;
			node->open(this, start_x, start_y, out_w, out_h);

			std::unique_ptr<NodeStackInfo> closer = std::make_unique<NodeStackInfo>(node, CLOSE_NODE, node_info->parent_closer, start_x, start_y, out_w, out_h);
			NodeStackInfo* ptr = closer.get();
			stack.insert(stack.begin(), move(closer));

			for (auto c : node->children()) {
				stack.insert(stack.begin(), std::make_unique<NodeStackInfo>(c, OPEN_NODE, ptr));
			}
		} else if (node_info->type == CLOSE_NODE) {
			int out_w, out_h, start_x, start_y;
			out_w = node_info->w;
			out_h = node_info->h;
			start_x = node_info->x;
			start_y = node_info->y;

			node->close(this, start_x, start_y, out_w, out_h);
			if (node->interactive()) {
				interactive_nodes.insert(interactive_nodes.begin(), {node, start_x, start_y, out_w, out_h});
			}

			drawStack.insert(drawStack.begin(), std::make_unique<NodeStackInfo>(node, CLOSE_NODE, nullptr, start_x, start_y, out_w, out_h));
			
			int parent_w, parent_h, parent_x, parent_y;
			NodeStackInfo* parent_info = node_info->parent_closer;
			if (parent_info != nullptr) {
				parent_w = parent_info->w;
				parent_h = parent_info->h;
				parent_x = parent_info->x;
				parent_y = parent_info->y;

				parent_info->node->child_closed(this, start_x, start_y, out_w, out_h, parent_x, parent_y, parent_w, parent_h);
				parent_info->w = parent_w;
				parent_info->h = parent_h;
				parent_info->x = parent_x;
				parent_info->y = parent_y;
			}
		}
	}
	resize(x(), y(), w(), cursor_y - y());
}

void HTMLPage::drawChildren(std::vector<std::unique_ptr<NodeStackInfo>>& drawStack) {
	while (drawStack.size() > 0) {
		// A backwards order (we start from the closing of <html> and move up from there), but this works for drawing.
		std::unique_ptr<NodeStackInfo> node_info = move(drawStack.front());
		drawStack.erase(drawStack.begin());

		node_info->node->draw(node_info->x, node_info->y, node_info->w, node_info->h, this);
	}
}

void HTMLPage::measureAndDraw() {
	std::unique_ptr<NodeStackInfo> _root = std::make_unique<NodeStackInfo>(root, OPEN_NODE, nullptr);
	std::vector<std::unique_ptr<NodeStackInfo>> stack = {};
	stack.emplace_back(std::move(_root));

	std::vector<std::unique_ptr<NodeStackInfo>> drawStack = {};

	measureChildren(stack, drawStack);
	drawChildren(drawStack);
}

void HTMLPage::draw() {
	Fl_Group::draw();
	// TODO: Use damage mask.
	if (root == nullptr) {
		throw std::logic_error("HTMLPage root not defined.");
	} else {
		measureAndDraw();
	}
}

#pragma endregion drawHTML

#pragma region interaction

bool HTMLPage::getInteractiveFromPos(int x, int y, HTMLNodePtr& out) {
	for (auto c : interactive_nodes) {
		if (x >= c.x && x <= c.x + c.w && y >= c.y && y <= c.y + c.h) {
			out = c.node;
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
		rendered->click(x, y, this);
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

void clearDraw(void* window) {
	static_cast<HTMLWindow*>(window)->redraw();
}

#pragma endregion interaction