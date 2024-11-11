#include "tags.hpp"
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>
#include <FL/Fl.H>
#include <typeinfo>
#include <util/base_sounds.hpp>

void HTMLNode::parseChildren(std::shared_ptr<RootNode> root, xmlpp::Element* const element) {
	for (auto child : element->get_children()) {
		Glib::ustring name = child->get_name();

		parseChild(root, child, name);
	}
}

void HTMLNode::parseChild(std::shared_ptr<RootNode> root, xmlpp::Node* node, Glib::ustring node_name) {
	if (node_name == "p") {
		_children.push_back(std::make_shared<P>(root, std::shared_ptr<HTMLNode>(this), node));
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

Body::Body(xmlpp::Element* const root, int x, int y, int w, int h) : Fl_Group(x, y, w, h), HTMLNode(nullptr, nullptr) {
	parseChildren(std::shared_ptr<RootNode>(this), root);
	end();
}

void Body::draw() {
	int x, y, w, h;
	x = Fl_Group::x();
	y = Fl_Group::y() + fl_height() + fl_descent();
	w = Fl_Group::w();
	h = Fl_Group::h();
	
	drawChildren(x, y, w, h);
	resizable(NULL);
	resize(Fl_Group::x(), Fl_Group::y(), w, h + fl_descent());
	resizable(this);
}

int Body::handle(int event) {
	int x = Fl::event_x();
	int y = Fl::event_y();

	if (_enteredHandler != nullptr && 
		(event == FL_LEAVE || 
			(event == FL_MOVE && 
			(x < _enteredHandler->nodeX() || x > _enteredHandler->nodeX() + _enteredHandler->nodeW() || y < _enteredHandler->nodeY() || _enteredHandler->nodeH()))
		)
	) {
		int out = _enteredHandler->handleEvent(FL_LEAVE);
		if (out != 0) {
			_enteredHandler = nullptr;
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
			int out = node->handleEvent(event);
			if (out != 0) {
				if (send_event == FL_ENTER) {
					_enteredHandler = node;
				}
				return out;
			}
		}
	}

	if (event == FL_ENTER) {
		return 1;
	} else {
		return 0;
	}
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

	if (position_info & TextPositionInfo::LAST) {
		size_t j;
		for (j = _content.length() - 1; j >= 0; j--) {
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

	for (int ptr = 0; ptr < _content.length(); ptr++, size++) {
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
	_node_y = y;

	int out_w, out_h = 0;
	
	fl_font(FL_HELVETICA, FL_NORMAL_SIZE);
	fl_color(FL_BLACK);
	for (auto c : _content_info) {
		if (x + (int)c.width > (w - x_margin)) {
			x = x_margin;

			int add = _base_content_h + _base_content_descent;
			y += add;
			
			out_w = w;
			out_h += add;
		}

		fl_draw(c_str + c.ptr, c.buf_size, x, y);
		x += (int)c.width;

		if (out_w < w) {
			out_w += (int)c.width;
		}
	}
	
	w = _node_w = out_w;
	h = _node_h = out_h;
}

P::P(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, xmlpp::Node* const node) : HTMLNode(root, parent) {
	parseChildren(root, dynamic_cast<xmlpp::Element*>(node));
	_root->addInteractive(std::shared_ptr<HTMLNode>(this));
}

void P::parseChild(std::shared_ptr<RootNode> root, xmlpp::Node* node, Glib::ustring node_name) {
	int position = ((node->get_next_sibling() == nullptr) << 1) | (node->get_previous_sibling() == nullptr);
	if (auto text = dynamic_cast<xmlpp::TextNode*>(node)) {
		_children.push_back(std::make_shared<Text>(root, std::shared_ptr<HTMLNode>(this), text, position));
	} else if (node_name == "a") {
		if (auto t = dynamic_cast<xmlpp::TextNode*>(node->get_first_child())) {
			_children.push_back(std::make_shared<A>(root, std::shared_ptr<HTMLNode>(this), t, position));
		}
	} 
}

void P::drawChildren(int& x, int& y, int& w, int& h) {
	int curr_x = _node_x = x;
	int curr_y = _node_y = y;

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

int A::handleEvent(int event) {
	if (event == FL_ENTER) {
		fl_message("TEST");
		return 1;
	}
	return 0;
}

/*
void HTMLNode::init() {
	auto color_prop = _attributes.find("color");
	if (color_prop != _attributes.end()) {
		color = std::stoi(color_prop->second);
	}
	auto background_color_prop = _attributes.find("background-color");
	if (background_color_prop != _attributes.end()) {
		background_color = std::stoi(background_color_prop->second);
	}
	return;
}

void HTMLNode::open(HTMLPage*, int&, int&, int&, int&) {
	return;
}

void HTMLNode::close(HTMLPage*, int&, int&, int&, int&) {
	return;
}

void HTMLNode::child_closed(HTMLPage*, const int child_x, const int child_y, const int child_w, const int child_h, int& start_x, int& start_y, int& out_w, int& out_h) {
	bool resetY = false;
	if (child_x < start_x) {
		start_x = child_x;
		resetY = true;
	}
	if (child_y < start_y || resetY) {
		start_y = child_y;
	}
	int localized_w = (child_x + child_w) - start_x;
	if (localized_w > out_w) {
		out_w = localized_w;
	}

	int localized_h = (child_y + child_h) - start_y;
	if (localized_h > out_h) {
		out_h = localized_h;
	}
}

void HTMLNode::click(int, int, HTMLPage*) {
	return;
}

void HTMLNode::draw(const int x, const int y, const int w, const int h, HTMLPage* current_page) {
	if (current_page->getHovered() == _id) {
		fl_draw_box(FL_FLAT_BOX, x, y, w, h, FL_BLUE);
		fl_color(FL_WHITE);
	} else {
		fl_draw_box(FL_FLAT_BOX, x, y, w, h, background_color);
		fl_color(color);
	}
}

void HTMLNode::hover(int, int, HTMLPage* current_page) {
	if (current_page->getHovered() != _id) {
		current_page->setHovered(_id);
		current_page->redraw();
	}
	current_page->parent_window->cursor(cursor);
}

void Text::open(HTMLPage* current_page, int& start_x, int& start_y, int& out_w, int& out_h) {
	out_w = current_page->w();
	out_h = 0;

	fl_font(FL_HELVETICA, 14);
	fl_measure(_data.c_str(), out_w, out_h);

	int height_buffer = current_page->getHeightBuffer();

	// TODO: Cut text up into chunks and wrap from that?
	if (start_x + out_w >= current_page->w()) {
		start_x = current_page->x();
		start_y += height_buffer;
		height_buffer = 0;
	}
	
	int cursor_x = start_x;
	int cursor_y = start_y;
	cursor_x += out_w;

	height_buffer = out_h;

	// TODO: Is this hack okay? Does it not work with other displays?
	current_page->setCursor(cursor_x, cursor_y);
	current_page->setHeightBuffer(height_buffer);
}

void Text::draw(const int x, const int y, const int w, const int h, HTMLPage* current_page) {
	HTMLNode::draw(x, y, w, h, current_page);
	fl_font(FL_HELVETICA, 14);
	fl_draw(_data.c_str(), x, y, w, h, FL_ALIGN_WRAP | FL_ALIGN_CENTER);
}

void A::click(int, int, HTMLPage* current_page) {
	auto search = _attributes.find("href");
	if (search != _attributes.end()) {
		// TODO: Move on-click logic to python scripting (?)
		
		windowCreation constructor;
		if (current_page->parent_window->getLinkedWindow(search->second, constructor)) {
			clickSound();
			auto window = constructor(current_page->parent_window->x() + 10, current_page->parent_window->y() + 10, current_page->parent_window->w(), current_page->parent_window->h());
			window->show();
		}
	}
}

void A::init() {
	for (auto c: _children) {
		if (typeid(*c).hash_code() == typeid(Text).hash_code()) {
			c->setColor(color);
		}
	}
}

void P::child_closed(HTMLPage*, const int child_x, const int child_y, const int child_w, const int child_h, int& start_x, int& start_y, int& out_w, int& out_h) {
	int localized_w = (child_x + child_w) - start_x;
	if (localized_w > out_w) {
		out_w = localized_w;
	}

	int localized_h = (child_y + child_h) - start_y;
	if (localized_h > out_h) {
		out_h = localized_h;
	}
}

void P::close(HTMLPage* current_page, int&, int& start_y, int&, int& out_h) {
	// We don't want to modify start_y, since that dictates this element's starting position.
	int cursor_x, cursor_y;
	current_page->getCursor(cursor_x, cursor_y);
	// The difference between the cursor y and where the element ends.
	int height_diff = (start_y + out_h) - cursor_y;
	cursor_y += height_diff + 20;
	current_page->setHeightBuffer(0);
	current_page->setCursor(current_page->x(), cursor_y);
}


void Img::init() {
	auto src = _attributes.find("src");
	
	if (src != _attributes.end()) {
		box = std::make_unique<ImageBox>(src->second.c_str());
	}
}

void Img::open(HTMLPage* current_page, int&, int&, int&, int&) {
	if (box == nullptr) {
		return;
	}
	int cursor_x, cursor_y;
	current_page->getCursor(cursor_x, cursor_y);
	int img_w = current_page->w() * 3/4;

	int img_x = current_page->x() + (current_page->w() - current_page->x())/2 - img_w/2;

	int full_w, full_h;
	box->getFullDimensions(full_w, full_h);
	double ratio = (double)full_h/(double)full_w;
	int img_h = ratio * img_w;

	box->prepareDraw(img_x, cursor_y, img_w, img_h);

	cursor_y += img_h + 20;

	current_page->setCursor(cursor_x, cursor_y);
}
*/