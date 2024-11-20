#include "tags.hpp"
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>
#include <FL/Fl.H>
#include <typeinfo>
#include <util/base_sounds.hpp>

#include "browser.hpp"

void HTMLNode::parseChildren(std::shared_ptr<RootNode> root, xmlpp::Element* const element) {
	for (auto child : element->get_children()) {
		Glib::ustring name = child->get_name();

		parseChild(root, child, name);
	}
}

void HTMLNode::parseChild(std::shared_ptr<RootNode> root, xmlpp::Node* node, Glib::ustring node_name) {
	if (node_name == "p") {
		_children.push_back(std::make_shared<P>(root, std::shared_ptr<HTMLNode>(this), node));
	} else if (node_name == "img") {
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

Body::Body(std::shared_ptr<Fl_Window> parent, xmlpp::Element* const root, int x, int y, int w, int h) : Fl_Group(x, y, w, h), HTMLNode(nullptr, nullptr), _parent(parent) {
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

Text::Text(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, xmlpp::TextNode* text_node, int position_info) : HTMLNode(root, parent) {
	if (text_node == nullptr) {
		return;
	}
	_content = text_node->get_content();
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

	int out_w, out_h = 0;

	
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

P::P(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, xmlpp::Node* const node) : HTMLNode(root, parent) {
	parseChildren(root, dynamic_cast<xmlpp::Element*>(node));
	_parent->addInteractive(std::shared_ptr<HTMLNode>(this));
}

void P::parseChild(std::shared_ptr<RootNode> root, xmlpp::Node* node, Glib::ustring node_name) {
	int position = ((node->get_next_sibling() == nullptr) << 1) | (node->get_previous_sibling() == nullptr);
	if (auto text = dynamic_cast<xmlpp::TextNode*>(node)) {
		_children.push_back(std::make_shared<Text>(root, std::shared_ptr<HTMLNode>(this), text, position));
	} else if (node_name == "a") {
		_children.push_back(std::make_shared<A>(root, std::shared_ptr<HTMLNode>(this), node, position));
	} 
}

void P::drawChildren(int& x, int& y, int& w, int& h) {
	int curr_x = _node_x = x;
	int curr_y = _node_y = y;

	_node_y -= fl_height();

	int p_w, p_h = 0;

	int out_w, out_h;
	for (auto c : _children) {
		out_w = w;
		out_h = h;
		c->drawChildren(curr_x, curr_y, out_w, out_h);

		p_w = std::min(p_w + out_w, w);
		p_h += out_h;
	}

	x = x_margin;
	p_h += fl_height() + fl_descent();
	

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

A::A(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, xmlpp::Node* node, int position_info) : Text(root, parent, dynamic_cast<xmlpp::TextNode*>(node->get_first_child()), position_info) {
	if (auto e = dynamic_cast<xmlpp::Element*>(node)) {
		if (auto href = e->get_attribute("href")) {
			std::string href_val = href->get_value();

			bool is_file = false;
			for (auto c : href_val) {
				if (c == '/') {
					is_file = true;
					continue;
				}

				if (is_file) {
					filename += c;
				} else {
					site += c;
				}
			}
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
		newWindow(site, filename, _root->parentX() + 10, _root->parentY() + 10, _root->parentW(), _root->parentH());
		return 1;
	}
	return 0;
}

Img::Img(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, xmlpp::Node* const node) : HTMLNode(root, parent) {
	if (auto i = dynamic_cast<xmlpp::Element*>(node)) {
		auto a = i->get_attribute("src");
		if (a != nullptr) {
			Glib::ustring src = a->get_value();
			box = std::make_unique<ImageBox>(src.c_str());
		}
	}
}

void Img::drawChildren(int& x, int& y, int& w, int& h) {
	w = w * 3/4;

	int full_w, full_h;
	box->getFullDimensions(full_w, full_h);
	double ratio = (double)full_h/(double)full_w;
	h = ratio * w;

	box->prepareDraw(x_margin * 2, y, w, h);
	box->draw();

	y += 20;
}