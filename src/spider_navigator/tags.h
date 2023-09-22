#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <FL/Enumerations.H>
#include "page.h"

class HTMLPage;

class HTMLNode {
	protected:
	Fl_Cursor cursor = FL_CURSOR_DEFAULT;
	Fl_Color color = FL_FOREGROUND_COLOR;

	
	std::string _data;
	std::vector<std::shared_ptr<HTMLNode>> _children;
	std::unordered_map<std::string, std::string> _attributes;
	std::shared_ptr<HTMLNode> _parent;

	public:
	const std::shared_ptr<HTMLNode> parent() const { return _parent; }
	void setParent(std::shared_ptr<HTMLNode> p) { _parent = p; }
	const std::vector<std::shared_ptr<HTMLNode>> children() const { return _children; } //TODO: FIX THIS
	const std::unordered_map<std::string, std::string> attributes() const { return _attributes; }
	const std::string data() const { return _data; }
	const Fl_Color getColor() const { return color; }
	void setColor(Fl_Color c) { color = c; }

	virtual void init();
	virtual void open(HTMLPage* current_page, int& out_w, int& out_h);
	virtual void close(HTMLPage* current_page);
	// Does this node need to have stuff like onHover, onClick, etc.
	virtual bool interactive() { return false; }
	// Draw using the current x and y provided. Passed as reference so they're modifiable.
	// Passing the current page because this node has to be shared with all pages rendering.
	virtual void click(int x, int y, HTMLPage* current_page);
	virtual void hover(int x, int y, HTMLPage* current_page);

 
	HTMLNode(const char* dat, std::vector<std::shared_ptr<HTMLNode>> c, std::unordered_map<std::string, std::string> attr) : _data(dat), _children(c), _attributes(attr) {
		
	}
};

typedef std::shared_ptr<HTMLNode> HTMLNodePtr;

class Text : public HTMLNode {
	public:
	Text(const char* dat, std::vector<std::shared_ptr<HTMLNode>> c, std::unordered_map<std::string, std::string> attr) : HTMLNode(dat, c, attr) {
		cursor = FL_CURSOR_INSERT;
	}
	virtual bool interactive() { return true; }
	void open(HTMLPage* current_page, int& out_w, int& out_h);
};

class A : public HTMLNode {
	public:
	virtual bool interactive() { return true; }
	void click(int x, int y, HTMLPage* current_page);
	void init();
	A(const char* dat, std::vector<std::shared_ptr<HTMLNode>> c, std::unordered_map<std::string, std::string> attr) : HTMLNode(dat, c, attr) {
		cursor = FL_CURSOR_HAND;
		// TODO: Use some sort of palette constants.
		color = 4;
	}
};

class P : public HTMLNode {
	public:
	using HTMLNode::HTMLNode;
	void close(HTMLPage* current_page);
};