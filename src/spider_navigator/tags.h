#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

class HTMLNode {
	public:
	const char* data;
	const vector<shared_ptr<HTMLNode>> children;
	const unordered_map<string, string> attributes;
	// Does this node need to have stuff like onHover, onClick, etc.
	const bool interactive = false;

	protected:
	int x, y, w, h = 0;
	Fl_Cursor cursor = FL_CURSOR_DEFAULT;
	Fl_Color color = FL_FOREGROUND_COLOR;
	shared_ptr<HTMLNode> parent;

	public:
	shared_ptr<HTMLNode> parent() { return parent; }
	void setParent(shared_ptr<HTMLNode> p) { parent = p; }

	// Draw using the current x and y provided. Passed as reference so they're modifiable.
	// Passing the current page because this node has to be shared with all pages rendering.
	virtual void open(HTMLPage* current_page) {}
	virtual void close(HTMLPage* current_page) {}
	virtual void click(int x, int y, HTMLPage* current_page) {}
	virtual void hover(int x, int y, HTMLPage* current_page) { current_page->parent_window->cursor(cursor); }

	HTMLNode(const char* dat, const vector<shared_ptr<HTMLNode>> c, unordered_map<string, string> attr) : data(dat), children(c), attributes(attr) {
		x, y, w, h = 0;
	};
};

typedef shared_ptr<HTMLNode> HTMLNodePtr;

class Text : public HTMLNode {
	const bool interactive = true;
	void open(HTMLPage* current_page);
};

class A : public HTMLNode {
	const bool interactive = true;
	Fl_Cursor cursor = FL_CURSOR_HAND;
	// TODO: Use some sort of palette constants.
	Fl_Color color = 4;
	void click(int x, int y, HTMLPage* current_page);
};

class P : public HTMLNode {
	void close(HTMLPage* current_page);
};