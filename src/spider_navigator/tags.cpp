#include "tags.hpp"
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>
#include <FL/Fl.H>
#include <typeinfo>

#ifdef __cpp_lib_format
#include <format>
#endif

#include <util/base_sounds.hpp>

#include "browser.hpp"

HTMLNode::HTMLNode(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent) { 
	_root = root;
	_parent = parent;

	if (_parent != nullptr) {
		_background_color = parent->backgroundColor();
		_text_color = parent->textColor();

		_highlight_bg = parent->highlightBackground();
		_highlight_text = parent->highlightText();
	}
}

void HTMLNode::parseChildren(std::shared_ptr<RootNode> root, htmlNodePtr const element) {
	if (element->properties != nullptr) {
		xmlAttrPtr property = element->properties;
		while (property != nullptr) {
			if (property->children == nullptr) {
				continue;
			}

			if (strncmp((char*)property->name, "background-color", 17) == 0) {
				_background_color = std::stoi((char*)property->children->content);
			} else if (strncmp((char*)property->name, "color", 6) == 0) {
				_text_color = std::stoi((char*)property->children->content);
			}

			property = property->next;
		}
	}

	htmlNodePtr child = element->children;
	while (child != nullptr) {
		const xmlChar* name = child->name;
		parseChild(root, child, name);

		child = child->next;
	}
}

void HTMLNode::parseChild(std::shared_ptr<RootNode> root, htmlNodePtr node, const xmlChar * node_name) {
	if (strncmp((char*)node_name, "p", 2) == 0) {
		_children.push_back(std::make_shared<P>(root, std::shared_ptr<HTMLNode>(this), node));
	} else if (strncmp((char*)node_name, "img", 4) == 0) {
		_children.push_back(std::make_shared<Img>(root, std::shared_ptr<HTMLNode>(this), node));
	}
}

void HTMLNode::drawChildren(int& x, int& y, int& w, int& h) {
	_node_x = x;
	int curr_y = _node_y = y;

	int out_w, out_h;
	int max_w = 0;
	for (auto c : _children) {
		out_w = w;
		out_h = h;
		c->drawChildren(x, curr_y, out_w, out_h);
		
		max_w = std::max(out_w, max_w);
		curr_y += out_h;
	}

	w = _node_w = max_w;
	h = _node_h = curr_y - y;
}

int HTMLNode::handleEvent(int event) {
	int x = Fl::event_x();
	int y = Fl::event_y();

	if (_enteredHandler != nullptr && 
		(event == FL_LEAVE || 
			(event == FL_MOVE && 
			(x < _enteredHandler->nodeX() || x > _enteredHandler->nodeX() + _enteredHandler->nodeW() || y < _enteredHandler->nodeY() ||y > _enteredHandler->nodeY() + _enteredHandler->nodeH()))
		)
	) {
		int out = _enteredHandler->handleEvent(FL_LEAVE);
		if (out != 0) {
			_enteredHandler = nullptr;
			if (event == FL_MOVE) {
				handleChildLeave();
			}
			return out;
		}
	}

	for (auto node : _interactiveNodes) {
		int node_x = node->nodeX();
		int node_y = node->nodeY();
		if (x > node_x && x < node_x + node->nodeW() && y > node_y && y < node_y + node->nodeH()) {
			int send_event = event;
			if (_enteredHandler == nullptr && (event & (FL_MOVE | FL_ENTER))) {
				send_event = FL_ENTER;
			}
			int out = node->handleEvent(send_event);
			if (out != 0) {
				if (send_event == FL_ENTER) {
					_enteredHandler = node;
				}
				return out;
			}
		}
	}

	return 0;
}

Body::Body(std::shared_ptr<Fl_Window> parent, htmlNodePtr const root, int x, int y, int w, int h) : Fl_Group(x, y, w, h), HTMLNode(nullptr, nullptr), _parent(parent) {
	parseChildren(std::shared_ptr<RootNode>(this), root);
	end();
}

void Body::draw() {
	int x, y, w, h;
	x = Fl_Group::x() + x_margin;
	y = Fl_Group::y() + fl_height() + fl_descent();
	w = Fl_Group::w();
	h = Fl_Group::h();

	fl_draw_box(FL_FLAT_BOX, x, Fl_Group::y(), w, h, _background_color);
	
	drawChildren(x, y, w, h);
	resizable(NULL);
	resize(Fl_Group::x(), Fl_Group::y(), w, h + fl_descent());
	resizable(this);
}

int Body::handle(int event) {
	return handleEvent(event);
}

double Text::addContent(int ptr, int& start_ptr, int& size, std::string& word) {
	double w = fl_width(word.c_str());
	_content_info.push_back(TextInfo{
		start_ptr, size, w,
	});
	
	start_ptr = ptr;
	size = 0;
	word.clear();

	return w;
}

Text::Text(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, htmlNodePtr text_node, int position_info) : HTMLNode(root, parent) {
	if (text_node == nullptr) {
		return;
	}
	_content = std::string((char*)text_node->content);
	_content_w = 0;

	if (position_info & TextPositionInfo::FIRST) {
		size_t i;
		for (i = 0; i < _content.length(); i++) {
			if (!iswspace(_content[i])) {
				break;
			}
		}

		_content.erase(0, i);
	}

	size_t content_length = _content.length();

	if (position_info & TextPositionInfo::LAST) {
		size_t j;
		for (j = content_length - 1; j < content_length; j--) {
			if (!iswspace(_content[j])) {
				break;
			}
		}

		_content.resize(j + 1);
	}

	fl_font(FL_HELVETICA, FL_NORMAL_SIZE);

	const char* c_str = _content.c_str();

	int start_ptr = 0;
	std::string word;

	bool was_space = false;
	int size = 0;

	for (size_t ptr = 0; ptr < _content.length(); ptr++, size++) {
		char c = c_str[ptr];
		word += c;

		int is_space = iswspace(c);
		if (is_space && !was_space) {
			was_space = true;

			_content_w += addContent(ptr, start_ptr, size, word);
		} else if (!is_space && was_space) {
			was_space = false;

			word.pop_back();
			
			_content_w += addContent(ptr, start_ptr, size, word);

			word += c;
		}
	}

	_content_w += addContent(0, start_ptr, size, word);
	
	_base_content_h = fl_height();
	_base_content_descent = fl_descent();
}

void Text::drawChildren(int& x, int& y, int& w, int& h) {
	const char* c_str = _content.c_str();

	_node_x = x;
	_node_y = y - _base_content_h;
	_node_h = 0;

	int out_w = 0, out_h = 0;

	
	fl_font(FL_HELVETICA, FL_NORMAL_SIZE);
	fl_color(_text_color);
	for (auto iter = _content_info.begin(); iter != _content_info.end(); iter++) {
		auto c = *iter;

		if (x + (int)c.width > (w - x_margin)) {
			x = x_margin;

			int add = _base_content_h + _base_content_descent;
			y += add;

			out_h += add;
			_node_h += add;
			
			if (iter == _content_info.begin()) {
				_node_x = x;
				_node_y += add;
				_node_h = 0;
			} else {
				out_w = w;
			}
		}
		
		if (highlight) {
			fl_draw_box(FL_FLAT_BOX, x, y - _base_content_h, c.width, _base_content_h + _base_content_descent, _highlight_bg);
			fl_color(_highlight_text);
		}

		fl_draw(c_str + c.ptr, c.buf_size, x, y);
		x += (int)c.width;

		if (out_w < w) {
			out_w += (int)c.width;
		}
	}
	
	w = _node_w = out_w;
	h = out_h;
	_node_h += _base_content_h + _base_content_descent;
}

P::P(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, htmlNodePtr const node) : HTMLNode(root, parent) {
	parseChildren(root, node);
	_parent->addInteractive(std::shared_ptr<HTMLNode>(this));
}

void P::parseChild(std::shared_ptr<RootNode> root, htmlNodePtr node, const xmlChar* node_name) {
	int position = ((node->next == nullptr) << 1) | (node->prev == nullptr);
	if (node->type == XML_TEXT_NODE) {
		_children.push_back(std::make_shared<Text>(root, std::shared_ptr<HTMLNode>(this), node, position));
	} else if (strncmp((char*)node_name, "a", 2) == 0) {
		_children.push_back(std::make_shared<A>(root, std::shared_ptr<HTMLNode>(this), node, position));
	} 
}

void P::drawChildren(int& x, int& y, int& w, int& h) {
	int curr_x = _node_x = x;
	int curr_y = _node_y = y;

	_node_y -= fl_height();

	int p_w = 0, p_h = 0;

	int out_w = 0, out_h;
	for (auto c : _children) {
		out_w = w;
		out_h = h;
		c->drawChildren(curr_x, curr_y, out_w, out_h);

		p_w = std::min(p_w + out_w, w);
		p_h += out_h;
	}

	x = x_margin;
	p_h += fl_height() + fl_descent() + 20;
	

	w = _node_w = p_w;
	h = _node_h = p_h;
}

int P::handleEvent(int event) {
	int out = HTMLNode::handleEvent(event);
	if (out != 0) {
		return out;
	}

	if (event == FL_ENTER) {
		setChildrenHighlight(true);
		_root->redraw();
		return 1;
	} else if (event == FL_LEAVE) {
		setChildrenHighlight(false);
		_root->redraw();
		return 1;
	}
	return 0;
}

void P::handleChildLeave() {
	setChildrenHighlight(true);
	_root->redraw();
}

void P::setChildrenHighlight(bool highlight) {
	for (auto c : _children) {
		if (auto t = dynamic_cast<Text*>(c.get())) {
			if (dynamic_cast<A*>(c.get()) == nullptr) {
				t->highlight = highlight;
			}
		}
	}
}

A::A(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, htmlNodePtr node, int position_info) : Text(root, parent, node->children, position_info) {
	if (node->type == XML_ELEMENT_NODE) {
		xmlAttrPtr property = node->properties;
		while (property != nullptr) {
			if (property->children == nullptr) {
				continue;
			}

			if (strncmp((char*)property->name, "href", 5) == 0) {
				filepath = std::string((char*)property->children->content);

				#ifdef __cpp_lib_format
				full_path = std::format("spider_navigator/{0}", filepath);
				#else
				full_path = "spider_navigator/" + filepath;
				#endif

				bool is_file = false;
				for (auto c : filepath) {
					if (c == '/' && !is_file) {
						is_file = true;
						continue;
					}

					if (is_file) {
						filename += c;
					} else {
						site += c;
					}
				}
				break;
			}

			property = property->next;
		}
	}
	_text_color = 4;
	_parent->addInteractive(std::shared_ptr<HTMLNode>(this));

	// Hack: avoid A tags appearing on one line.
	_content_info.clear();
	_content_info.push_back(TextInfo{
		0,
		(int)_content.length(),
		_content_w
	});
}

int A::handleEvent(int event) {
	if (event == FL_ENTER) {
		dynamic_cast<P*>(_parent.get())->setChildrenHighlight(false);
		highlight = true;
		_root->redraw();
		_root->setCursor(FL_CURSOR_HAND);
		return 1;
	} else if (event == FL_LEAVE) {
		highlight = false;
		_root->setCursor(FL_CURSOR_DEFAULT);
		_root->redraw();
		return 1;
	} else if (event == FL_PUSH) {
		clickSound();
		Browser::NewWindow(site, filename, _root->parentX() + 10, _root->parentY() + 10, _root->parentW(), _root->parentH());
		return 1;
	}
	return 0;
}

void A::drawChildren(int& x, int& y, int& w, int& h) {
	if (Browser::VisitedPage(full_path)) {
		_text_color = visited_color;
	}
	Text::drawChildren(x, y, w, h);
}

Img::Img(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, htmlNodePtr const node) : HTMLNode(root, parent) {
	if (node->type == XML_ELEMENT_NODE) {
		xmlAttrPtr property = node->properties;
		while (property != nullptr) {
			if (property->children == nullptr) {
				continue;
			}

			if (strncmp((char*)property->name, "src", 4) == 0) {
				const char* src = (char*)property->children->content;
				box = std::make_unique<ImageBox>(src);
			}

			property = property->next;
		}
	}
}

void Img::drawChildren(int&, int& y, int& w, int& h) {
	w = w * 3/4;

	int full_w, full_h;
	box->getFullDimensions(full_w, full_h);
	double ratio = (double)full_h/(double)full_w;
	h = ratio * w;

	box->prepareDraw(x_margin * 2, y, w, h);
	box->draw();

	y += 20;
}