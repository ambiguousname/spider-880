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
	// Does this node need to have stuff like onHover, onClick, etc.
	bool _interactive = false;
	std::shared_ptr<HTMLNode> _parent;

	public:
	const std::shared_ptr<HTMLNode> parent() const { return _parent; }
	void setParent(std::shared_ptr<HTMLNode> p) { _parent = p; }
	bool interactive() { return _interactive; }
	const std::vector<std::shared_ptr<HTMLNode>> children() const { return _children; } //TODO: FIX THIS
	const std::unordered_map<std::string, std::string> attributes() const { return _attributes; }
	const std::string data() const { return _data; }

	// Draw using the current x and y provided. Passed as reference so they're modifiable.
	// Passing the current page because this node has to be shared with all pages rendering.
	virtual void open(HTMLPage* current_page, int& out_w, int& out_h);
	virtual void close(HTMLPage* current_page);
	virtual void click(int x, int y, HTMLPage* current_page);
	virtual void hover(int x, int y, HTMLPage* current_page);

 
	HTMLNode(const char* dat, std::vector<std::shared_ptr<HTMLNode>> c, std::unordered_map<std::string, std::string> attr) : _data(dat), _children(c), _attributes(attr) {
		
	}
};

typedef std::shared_ptr<HTMLNode> HTMLNodePtr;

class Text : public HTMLNode {
	bool _interactive = true;
	void open(HTMLPage* current_page, int& out_w, int& out_h);
	
	public:
	using HTMLNode::HTMLNode;
};

class A : public HTMLNode {
	bool interactive = true;
	Fl_Cursor cursor = FL_CURSOR_HAND;
	// TODO: Use some sort of palette constants.
	Fl_Color color = 4;
	void click(int x, int y, HTMLPage* current_page);
	public:
	using HTMLNode::HTMLNode;
};

class P : public HTMLNode {
	void close(HTMLPage* current_page);
	public:
	using HTMLNode::HTMLNode;
};