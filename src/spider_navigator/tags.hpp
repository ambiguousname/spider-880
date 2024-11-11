#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <FL/Fl_Group.H>
#include "util/image_box.hpp"
#include <libxml++/libxml++.h>

class Body;

typedef Body RootNode;

class HTMLNode {
	protected:
	std::shared_ptr<RootNode> _root;
	std::shared_ptr<HTMLNode> _parent;
	std::vector<std::shared_ptr<HTMLNode>> _children;

	void parseChildren(std::shared_ptr<RootNode> root, xmlpp::Element* const element);
	virtual void parseChild(std::shared_ptr<RootNode> root, xmlpp::Node* const node, Glib::ustring node_name);

	int x_margin = 0;

	int _node_x;
	int _node_y;
	int _node_w;
	int _node_h;

	public:
	int nodeX() const { return _node_x; }
	int nodeY() const { return _node_y; }
	int nodeW() const { return _node_w; }
	int nodeH() const { return _node_h; }
	virtual int handleEvent(int event) { return 0; }

	HTMLNode(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent) { _root = root; _parent = parent; }
	~HTMLNode() { _parent.reset(); for (auto c: _children) { c.reset(); } }
	
	/// @brief Draw the node at the given position.
	/// @param x X-position to draw of the node. The node can change its own starting position if it determines that there is not sufficient space. X can only go up, never down.
	/// @param y Y-position to draw of the node. The node can change its own starting position if it determines that there is not sufficient space. X can only go up, never down.
	/// @param w Pass the width of the parent node in, and get the width of the drawn node out.
	/// @param h Pass the height of the parent node in, and get the height of the drawn node out.
	virtual void drawChildren(int& x, int& y, int& w, int& h);
};

class Body : public Fl_Group, public HTMLNode {
	protected:
	std::vector<std::shared_ptr<HTMLNode>> _interactiveNodes;

	std::shared_ptr<HTMLNode> _enteredHandler;

	public:

	void addInteractive(std::shared_ptr<HTMLNode> node) { _interactiveNodes.push_back(node); }

	Body(xmlpp::Element* const root, int x, int y, int w, int h);
	void draw() override;
	int handle(int event);
};

struct TextInfo {
	int ptr;
	int buf_size;
	double width;
};

enum TextPositionInfo {
	NONE = 0,
	FIRST = 1,
	LAST = 2
};

class Text : public HTMLNode {
	protected:
	std::string _content;
	std::vector<TextInfo> _content_info;
	int _base_content_h;
	int _base_content_descent;
	double _content_w;

	double addContent(int ptr, int& start_ptr, int& size, std::string& word);

	public:
	bool highlight = false;
	
	Text(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, xmlpp::TextNode* text_node, int position_info);

	void drawChildren(int& x, int& y, int& w, int& h) override;
};

class A : public Text {
	public:
	A(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, xmlpp::TextNode* text_node, int position_info) : Text(root, parent, text_node, position_info) { _root->addInteractive(std::shared_ptr<HTMLNode>(this)); }

	int handleEvent(int event) override;
};

class P : public HTMLNode {
	protected:
	void parseChild(std::shared_ptr<RootNode> root, xmlpp::Node* const node, Glib::ustring node_name) override;	

	public:
	P(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, xmlpp::Node* const node);
	
	void drawChildren(int& x, int& y, int& w, int& h) override;

	int handleEvent(int event) override;
};

/*
class HTMLPage;

class HTMLNode {
	protected:
	const int _id = -1;

	Fl_Cursor cursor = FL_CURSOR_DEFAULT;
	Fl_Color color = FL_FOREGROUND_COLOR;
	Fl_Color background_color = FL_BACKGROUND_COLOR;

	
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
	
	// Measuring functions (for x, y, w, h):
	virtual void open(NODE_OPENER);
	virtual void close(NODE_CLOSER);
	virtual void child_closed(NODE_CHILD_CLOSER);

	// Actual function for drawing things like shapes and colors.
	virtual void draw(const int x, const int y, const int w, const int h, HTMLPage* current_page);

	// Does this node need to have stuff like onHover, onClick, etc.
	virtual bool interactive() { return false; }
	// Draw using the current x and y provided. Passed as reference so they're modifiable.
	// Passing the current page because this node has to be shared with all pages rendering.
	virtual void click(int x, int y, HTMLPage* current_page);
	virtual void hover(int x, int y, HTMLPage* current_page);

 
	HTMLNode(NODE_CONSTRUCTOR) : _id(id), _data(dat), _children(c), _attributes(attr) {
		
	}
	~HTMLNode() { _parent.reset(); for (auto c: _children) { c.reset(); } }
};

typedef std::shared_ptr<HTMLNode> HTMLNodePtr;

class Body : public HTMLNode {
	public:
	using HTMLNode::HTMLNode;
};

class Text : public HTMLNode {

	public:
	Text(NODE_CONSTRUCTOR) : HTMLNode(id, dat, c, attr) {
		cursor = FL_CURSOR_INSERT;
	}
	virtual bool interactive() { return true; }
	void open(NODE_OPENER) override;
	void draw(const int x, const int y, const int w, const int h, HTMLPage* current_page) override;
};

class A : public HTMLNode {
	public:
	bool interactive() { return true; }
	void click(int x, int y, HTMLPage* current_page);
	void init();
	A(NODE_CONSTRUCTOR) : HTMLNode(id, dat, c, attr) {
		cursor = FL_CURSOR_HAND;
		// TODO: Use some sort of palette constants.
		color = 4;
	}
};

class P : public HTMLNode {
	public:
	using HTMLNode::HTMLNode;
	void close(NODE_CLOSER);
	void child_closed(NODE_CHILD_CLOSER);
};

class Img : public HTMLNode {
	std::unique_ptr<ImageBox> box;
	public:
	using HTMLNode::HTMLNode;
	~Img() { box.release(); }
	void init();
	void open(NODE_OPENER);

	void draw(const int, const int, const int, const int, HTMLPage*) override { 
		box->draw();
	}
};*/