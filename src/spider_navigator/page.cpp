#include "page.h"
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include "pages/gertwig_blog/navsab.h"
#include "pages/deadbeef/deadbeef.h
#include <stdexcept>
#include <variant>

void aboutCallback(Fl_Widget*, void*) {
	// fl_message_icon();
	fl_alert("Bureau of Sabotage Network Navigator\nBy Brian Gertwig");
}

typedef HTMLWindow* (*page_create)(int, int, int, int);

void showHTMLPage(Fl_Widget* widget, void* pg) {
	page_create creator = static_cast<page_create>(pg);
	HTMLWindow* page = creator(widget->x() + 10, widget->y() + 10, widget->w(), widget->h());
	page->show();
}

struct Password {
	const char* password;
	Fl_Callback* callback;
	void* data = 0;
	int curr_index=0;
	bool operator==(const Password& other) {
		return strcmp(password, other.password) == 0;
	}
};

const Password passwords[] = {
	{"deadbeef", showHTMLPage, DeadbeefDeadbeefHTMLWindow::createWindow},
	{"feebdaed", showHTMLPage, DeadbeefFeebdaedHTMLWindow::createWindow},
};

int HTMLWindow::handle(int event) {
	if (event == FL_KEYDOWN) {
		const char* key =  Fl::event_text();
		if (key[0] != '\0'){
			typing_buffer.push_back(tolower(key[0]));
			if (typing_buffer.size() > 20) {
				typing_buffer.erase(typing_buffer.begin());
			}
			
			std::vector<Password> matches = {};

			for (auto p: passwords) {
				int size = sizeof(p.password)/sizeof(*p.password);
				if (p.password[size - 1] == typing_buffer.back()) {
					Password match = Password(p);
					match.curr_index = size - 1;
					matches.push_back(match);
				}
			}

			// Avoid integer underflow: https://stackoverflow.com/questions/4205720/iterating-over-a-vector-in-reverse-direction
			if (typing_buffer.size() > 1 && matches.size() > 0) {
				for (unsigned i = typing_buffer.size() - 1; i-- > 0; ) {
					bool pwd_found = false;
					for (auto m = matches.begin(); m != matches.end(); m++) {
						auto prev = m;
						m->curr_index -= 1;
						if (m->curr_index < 0) {
							pwd_found = true;
							m->callback(this, 0);
							break;
						} else if (m->password[m->curr_index] != typing_buffer[i]) {
							m++;
							matches.erase(prev);
							if (matches.size() == 0) {
								break;
							}
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

HTMLWindow::HTMLWindow(std::shared_ptr<HTMLNode> root, int x, int y, int w, int h) : Fl_Window(x, y, w, h), menu_bar(0, 0, w, 20) {
	menu_bar.add("NavSab");
	menu_bar.add("Help/About", FL_CTRL+'a', aboutCallback);
	menu_bar.add("Help/Website", FL_CTRL+'w', aboutWebsite);

	auto attributes = root->attributes();
	auto find_title = attributes.find("title");
	if (find_title != attributes.end()) {
		// Create a constant reference to the title so c_str doesn't bug out:
		title = find_title->second;
		label(title.c_str());
	}
	scrollbar = new Fl_Scroll(0, 20, w, h - 20);
	page = new HTMLPage(root, std::shared_ptr<HTMLWindow>(this), 0, 20, w, h - 20, 20);
	scrollbar->end();
	scrollbar->type(Fl_Scroll::VERTICAL);

	resizable(this);
	end();
}

bool HTMLWindow::getLinkedWindow(std::string name, windowCreation& out) {
	auto search = linked_windows.find(name);
	if (search != linked_windows.end()) {
		out = search->second;
		return true;
	}
	return false;
}

HTMLPage::HTMLPage(std::shared_ptr<HTMLNode> r, std::shared_ptr<HTMLWindow> parent, int x, int y, int w, int h, int horizontal_padding) : Fl_Group(x, y, w, h), interactive_nodes(), parent_window(parent), padding(horizontal_padding) {
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


void HTMLPage::drawChildren() {
	std::unique_ptr<NodeQueueInfo> _root = std::make_unique<NodeQueueInfo>(root, OPEN_NODE, nullptr);
	std::vector<std::unique_ptr<NodeQueueInfo>> queue = {};
	queue.emplace_back(std::move(_root));
	interactive_nodes.clear();

	cursor_x = x();
	cursor_y = y();
	while (queue.size() > 0) {
		std::unique_ptr<NodeQueueInfo> node_info = move(queue.front());
		queue.erase(queue.begin());

		std::shared_ptr<HTMLNode> node = node_info->node;
		if (node_info->type == OPEN_NODE) {

			int out_w, out_h, start_x, start_y;
			out_w = 0;
			out_h = 0;
			start_x = cursor_x;
			start_y = cursor_y;
			node->open(this, start_x, start_y, out_w, out_h);

			std::unique_ptr<NodeQueueInfo> closer = std::make_unique<NodeQueueInfo>(node, CLOSE_NODE, node_info->parent_closer, start_x, start_y, out_w, out_h);
			NodeQueueInfo* ptr = closer.get();
			queue.insert(queue.begin(), move(closer));

			for (auto c : node->children()) {
				queue.insert(queue.begin(), std::make_unique<NodeQueueInfo>(c, OPEN_NODE, ptr));
			}
		} else if (node_info->type == CLOSE_NODE) {
			int out_w, out_h, start_x, start_y;
			out_w = node_info->w;
			out_h = node_info->h;
			start_x = node_info->x;
			start_y = node_info->y;
			node->close(this, start_x, start_y, out_w, out_h);
			if (node->interactive()) {
				interactive_nodes.push_back({node, start_x, start_y, out_w, out_h});
			}
			
			int parent_w, parent_h, parent_x, parent_y;
			NodeQueueInfo* parent_info = node_info->parent_closer;
			if (parent_info != nullptr){
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
	resize(x(), y(), this->parent()->w() - 20, cursor_y - y());
}

void HTMLPage::draw() {
	Fl_Group::draw();
	// TODO: Use damage mask.
	if (root == nullptr) {
		throw std::logic_error("HTMLPage root not defined.");
	} else {
		drawChildren();
	}
}

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