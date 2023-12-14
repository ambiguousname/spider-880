#include "page.h"
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include "pages/gertwig_blog/navsab.h"
#include "pages/deadbeef/deadbeef.h"
#include "pages/deadbeef/feebdaed.h"
#include "pages/deadbeef/abababab.h"
#include "pages/deadbeef/babababa.h"
#include <stdexcept>
#include <util/base_sounds.h>

void aboutCallback(Fl_Widget*, void*) {
	// fl_message_icon();
	errorSound();
	fl_alert("Bureau of Sabotage Network Navigator\nBy Brian Gertwig");
}

typedef HTMLWindow* (*page_create)(int, int, int, int);

void showHTMLPageFromString(Fl_Widget* widget, void* str) {
	HTMLWindow* window = dynamic_cast<HTMLWindow*>(widget);

	std::string* string = (std::string*)str;
	windowCreation out;
	window->getLinkedWindow(*string, out);

	HTMLWindow* page = out(window->x() + 10, window->y() + 10, window->w(), window->h());
	page->show();
}

void showHTMLPage(Fl_Widget* widget, void* pg) {
	page_create creator = (page_create)(pg);
	HTMLWindow* window = dynamic_cast<HTMLWindow*>(widget);
	if (window == nullptr) {
		HTMLWindow* page = creator(10, 10, 300, 300);
		page->show();
		return;
	}
	HTMLWindow* page = creator(window->x() + 10, window->y() + 10, window->w(), window->h());
	page->show();
}

const Password const_passwords[] = {
	{"deadbeef", showHTMLPage, (void*)DeadbeefDeadbeefHTMLWindow::createWindow},
	{"feebdaed", showHTMLPage, (void*)DeadbeefFeebdaedHTMLWindow::createWindow},
	{"abababab", showHTMLPage, (void*)DeadbeefAbabababHTMLWindow::createWindow},
	{"babababa", showHTMLPage, (void*)DeadbeefBabababaHTMLWindow::createWindow},
};

HTMLWindow::HTMLWindow(std::shared_ptr<HTMLNode> root, int x, int y, int w, int h) : Fl_Window(x, y, w, h), menu_bar(0, 0, w, 20) {
	menu_bar.add("NavSab", 0, 0, 0, FL_MENU_INACTIVE);
	menu_bar.add("Help/About", FL_CTRL+'a', aboutCallback);
	menu_bar.add("Help/Website", FL_CTRL+'w', showHTMLPage, (void*)&GertwigBlogNavsabHTMLWindow::createWindow);

	auto attributes = root->attributes();
	auto find_title = attributes.find("title");
	if (find_title != attributes.end()) {
		// Create a constant reference to the title so c_str doesn't bug out:
		title = find_title->second;
		label(title.c_str());
	}

	for (auto p : const_passwords) {
		passwords.push_back(p);
	}
	auto pwds = attributes.find("passwords");
	if (pwds != attributes.end()) {

		std::string buf = "";
		std::string passwordName;

		for (auto c : pwds->second) {
			if (c == '=') {
				passwordName = buf;
				buf = "";
			} else if (c == ',' || c == '\0') {
				Password& a = passwords.emplace_back(Password {passwordName, showHTMLPageFromString, 0, buf});
				a.data = &a.str_data;
				buf = "";
				passwordName = "";
			} else {
				buf += c;
			}
		}
		if (buf.size() > 0 && passwordName.size() > 0) {
			Password& a = passwords.emplace_back(Password {passwordName, showHTMLPageFromString, 0, buf});
			a.data = &a.str_data;
		}
	}

	scrollbar = new Fl_Scroll(0, 25, w, h - 25);
	page = new HTMLPage(root, std::shared_ptr<HTMLWindow>(this), 0, 25, w, h - 25, 10);
	scrollbar->end();
	scrollbar->type(Fl_Scroll::VERTICAL);

	resizable(this);
}

bool HTMLWindow::getLinkedWindow(std::string name, windowCreation& out) {
	auto search = linked_windows.find(name);
	if (search != linked_windows.end()) {
		out = search->second;
		return true;
	}
	return false;
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

int HTMLWindow::handle(int event) {
	if (event == FL_KEYDOWN) {
		const char* key =  Fl::event_text();
		
		if (key[0] != '\0'){
			char key_l = tolower(key[0]);

			make_current();
			Fl_Fontsize old_size = fl_size();
			Fl_Color old_color = fl_color();
			fl_color(FL_RED);
			fl_font(fl_font(), 50);
			fl_draw(std::string(1, key_l).c_str(), 0, 0, w(), h(), FL_ALIGN_CENTER);
			fl_font(fl_font(), old_size);
			fl_color(old_color);
			if (!Fl::has_timeout(clearDraw, this)) {
				Fl::add_timeout(0.1, clearDraw, this);
			}

			typing_buffer.push_back(key_l);
			if (typing_buffer.size() > 20) {
				typing_buffer.erase(typing_buffer.begin());
			}
			
			std::vector<Password> matches = {};

			for (auto p: passwords) {
				size_t size = p.password.size();
				if (p.password[size - 1] == typing_buffer.back()) {
					Password match = Password(p);
					match.curr_index = size - 1;
					matches.push_back(match);
				}
			}

			// Avoid integer underflow: https://stackoverflow.com/questions/4205720/iterating-over-a-vector-in-reverse-direction
			if (typing_buffer.size() > 1 && matches.size() > 0) {
				for (size_t i = typing_buffer.size() - 1; i-- >= 0; ) {
					bool pwd_found = false;
					for (auto m = matches.begin(); m != matches.end();) {
						m->curr_index -= 1;
						if (m->curr_index < 0) {
							pwd_found = true;
							m->callback(this, m->data);
							break;
						} else if (m->password[m->curr_index] != typing_buffer[i]) {
							matches.erase(m);
						} else {
							m++;
						}
					}
					if (pwd_found || matches.size() == 0) {
						break;
					}
				}
			}
		}
	}
	return Fl_Window::handle(event);
}

#pragma endregion interaction