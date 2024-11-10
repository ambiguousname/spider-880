#include "tags.hpp"
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>
#include <typeinfo>
#include <util/base_sounds.hpp>

void HTMLNode::parseChildren(xmlpp::Element* const element) {
	for (auto child : element->get_children()) {
		Glib::ustring name = child->get_name();

		parseChild(child, name);
	}
}

void HTMLNode::parseChild(xmlpp::Node* node, Glib::ustring node_name) {
	if (node_name == "p") {
		_children.push_back(std::make_shared<P>(std::shared_ptr<HTMLNode>(this), node));
	}
}

void HTMLNode::drawChildren(int& x, int& y, int& w, int& h) {
	int curr_y = y;

	int out_w, out_h;
	int max_w = 0;
	for (auto c : _children) {
		out_w = w;
		out_h = h;
		c->drawChildren(x, curr_y, out_w, out_h);
		
		max_w = std::max(out_w, max_w);
		curr_y += out_h;
	}

	w = max_w;
	h = curr_y - y;
}

Body::Body(xmlpp::Element* const root, int x, int y, int w, int h) : Fl_Group(x, y, w, h), HTMLNode(nullptr) {
	parseChildren(root);
	end();
}

void Body::draw() {
	int x, y, w, h;
	x = this->x();
	y = this->y();
	w = this->w();
	h = this->h();
	
	drawChildren(x, y, w, h);
	resizable(NULL);
	resize(this->x(), this->y(), w, h);
	resizable(this);
}

Text::Text(std::shared_ptr<HTMLNode> parent, xmlpp::TextNode* text_node) : HTMLNode(parent) {
	_content = text_node->get_content();
	
	fl_font(FL_HELVETICA, FL_NORMAL_SIZE);
	_content_w = fl_width(_content.c_str(), _content.length());
	_base_content_h = fl_height();
}

void Text::drawChildren(int& x, int& y, int& w, int& h) {
	int height_draw = (((int)_content_w / w) + 1) * _base_content_h;
	int num_lines = ((int)_content_w / w) + 1;

	// TODO: Better wrapping.

	if (num_lines > 1) {
		x = x_margin;
		y += _base_content_h;
	}
	
	fl_font(FL_HELVETICA, FL_NORMAL_SIZE);
	fl_color(FL_BLACK);
	fl_draw(_content.c_str(), x, y, w, height_draw, FL_ALIGN_WRAP);
	
	w = std::min((int)_content_w, w);
	h = (num_lines - 1) * _base_content_h;
}

P::P(std::shared_ptr<HTMLNode> parent, xmlpp::Node* const node) : HTMLNode(parent) {
	parseChildren(dynamic_cast<xmlpp::Element*>(node));
}

void P::parseChild(xmlpp::Node* node, Glib::ustring node_name) {
	if (auto text = dynamic_cast<xmlpp::TextNode*>(node)) {
		_children.push_back(std::make_shared<Text>(std::shared_ptr<HTMLNode>(this), text));
	}
}

void P::drawChildren(int& x, int& y, int& w, int& h) {
	int curr_x = x;
	int curr_y = y;

	int out_w, out_h;
	for (auto c : _children) {
		out_w = w;
		out_h = h;
		c->drawChildren(curr_x, curr_y, out_w, out_h);

		curr_x += out_w;
		curr_y += out_h;
	}

	if (out_h == 0) {
		out_h = fl_height();
	}

	w = out_w;
	h = out_h;
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