#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <FL/Enumerations.H>
#include "util/image_box.h"
#include "page.h"

class HTMLPage;

#define NODE_CONSTRUCTOR const char* dat, std::vector<std::shared_ptr<HTMLNode>> c, std::unordered_map<std::string, std::string> attr

class HTMLNode {
	protected:
	Fl_Cursor cursor = FL_CURSOR_DEFAULT;
	Fl_Color color = FL_FOREGROUND_COLOR;

	
	std::string _data;
	std::vector<std::shared_ptr<HTMLNode>> _children;
	std::unordered_map<std::string, std::string> _attributes;
	std::shared_ptr<HTMLNode> _parent;

	public:
	std::shared_ptr<HTMLNode> parent() const { return _parent; }
	void setParent(std::shared_ptr<HTMLNode> p) { _parent = p; }

	std::vector<std::shared_ptr<HTMLNode>> children() const { return _children; }
	
	std::unordered_map<std::string, std::string> attributes() const { return _attributes; }

	std::string data() const { return _data; }

	Fl_Color getColor() const { return color; }
	void setColor(Fl_Color c) { color = c; }

	Fl_Cursor getCursor() const { return cursor; }

	virtual void init();
	virtual void open(HTMLPage* current_page, int& start_x, int& start_y, int& out_w, int& out_h);
	virtual void close(HTMLPage* current_page, int& start_x, int& start_y, int& out_w, int& out_h);
	virtual void child_closed(HTMLPage* current_page, const int child_x, const int child_y, const int child_w, const int child_h, int& start_x, int& start_y, int& out_w, int& out_h);
	// Does this node need to have stuff like onHover, onClick, etc.
	virtual bool interactive() { return false; }
	// Draw using the current x and y provided. Passed as reference so they're modifiable.
	// Passing the current page because this node has to be shared with all pages rendering.
	virtual void click(int x, int y, HTMLPage* current_page);
	virtual void hover(int x, int y, HTMLPage* current_page);

 
	HTMLNode(NODE_CONSTRUCTOR) : _data(dat), _children(c), _attributes(attr) {
		
	}
	~HTMLNode() { _parent.reset(); for (auto c: _children) { c.reset(); } }
};

typedef std::shared_ptr<HTMLNode> HTMLNodePtr;

class Text : public HTMLNode {
	public:
	Text(NODE_CONSTRUCTOR) : HTMLNode(dat, c, attr) {
		cursor = FL_CURSOR_INSERT;
	}
	virtual bool interactive() { return true; }
	void open(HTMLPage* current_page, int& start_x, int& start_y, int& out_w, int& out_h);
};

class A : public HTMLNode {
	public:
	bool interactive() { return true; }
	void click(int x, int y, HTMLPage* current_page);
	void init();
	A(NODE_CONSTRUCTOR) : HTMLNode(dat, c, attr) {
		cursor = FL_CURSOR_HAND;
		// TODO: Use some sort of palette constants.
		color = 4;
	}
	void child_closed(HTMLPage* current_page, const int child_x, const int child_y, const int child_w, const int child_h, int& start_x, int& start_y, int& out_w, int& out_h);
};

class P : public HTMLNode {
	public:
	using HTMLNode::HTMLNode;
	void close(HTMLPage* current_page, int& start_x, int& start_y, int& out_w, int& out_h);
	void child_closed(HTMLPage* current_page, const int child_x, const int child_y, const int child_w, const int child_h, int& start_x, int& start_y, int& out_w, int& out_h);
};

class Img : public HTMLNode {
	std::unique_ptr<ImageBox> box;
	public:
	using HTMLNode::HTMLNode;
	~Img() { box.release(); }
	void init();
	void open(HTMLPage* current_page, int& start_x, int& start_y, int& out_w, int& out_h);
};