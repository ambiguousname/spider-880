#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <FL/Fl_Group.H>
#include <FL/Fl_Window.H>
#include "util/image_box.hpp"
#include <libxml++/libxml++.h>

class Body;

typedef Body RootNode;

class HTMLNode {
	protected:
	std::shared_ptr<RootNode> _root;
	std::shared_ptr<HTMLNode> _parent;
	std::vector<std::shared_ptr<HTMLNode>> _children;
	
	std::vector<std::shared_ptr<HTMLNode>> _interactiveNodes;

	std::shared_ptr<HTMLNode> _enteredHandler;

	int _background_color = FL_BACKGROUND_COLOR;
	int _text_color = FL_FOREGROUND_COLOR;

	int _highlight_bg = FL_BLUE;
	int _highlight_text = FL_WHITE;

	void parseChildren(std::shared_ptr<RootNode> root, xmlpp::Element* const element);
	virtual void parseChild(std::shared_ptr<RootNode> root, xmlpp::Node* const node, Glib::ustring node_name);

	int x_margin = 15;

	int _node_x = -1;
	int _node_y = -1;
	int _node_w = -1;
	int _node_h = -1;

	public:
	int nodeX() const { return _node_x; }
	int nodeY() const { return _node_y; }
	int nodeW() const { return _node_w; }
	int nodeH() const { return _node_h; }

	int backgroundColor() const { return _background_color; }
	int textColor() const { return _text_color; }
	int highlightBackground() const { return _highlight_bg; }
	int highlightText() const { return _highlight_text; }

	virtual int handleEvent(int event);
	// Called if we're still in focus even after having left an interactive node child.
	virtual void handleChildLeave() {}

	void addInteractive(std::shared_ptr<HTMLNode> node) { _interactiveNodes.push_back(node); }

	HTMLNode(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent);
	~HTMLNode() { _parent.reset(); _root.reset(); _enteredHandler.reset(); for (auto c: _children) { c.reset(); } for (auto i : _interactiveNodes) { i.reset(); } }
	
	/// @brief Draw the node at the given position.
	/// @param x X-position to draw of the node. The node can change its own starting position if it determines that there is not sufficient space. X can only go up, never down.
	/// @param y Y-position to draw of the node. The node can change its own starting position if it determines that there is not sufficient space. X can only go up, never down.
	/// @param w Pass the width of the parent node in, and get the width of the drawn node out.
	/// @param h Pass the height of the parent node in, and get the height of the drawn node out.
	virtual void drawChildren(int& x, int& y, int& w, int& h);
};

class Body : public Fl_Group, public HTMLNode {
	protected:
	std::shared_ptr<Fl_Window> _parent;

	public:
	Body(std::shared_ptr<Fl_Window> parent, xmlpp::Element* const root, int x, int y, int w, int h);
	~Body() { _parent.reset(); }
	void draw() override;
	int handle(int event);

	void setCursor(Fl_Cursor cursor) { _parent->cursor(cursor); }
	int parentX() { return _parent->x(); }
	int parentY() { return _parent->y(); }
	int parentW() { return _parent->w(); }
	int parentH() { return _parent->h(); }
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
	protected:
	std::string site;
	std::string filename;

	public:
	A(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, xmlpp::Node* node, int position_info);

	int handleEvent(int event) override;
};

class P : public HTMLNode {
	protected:
	void parseChild(std::shared_ptr<RootNode> root, xmlpp::Node* const node, Glib::ustring node_name) override;	

	public:
	P(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, xmlpp::Node* const node);
	
	void drawChildren(int& x, int& y, int& w, int& h) override;

	void setChildrenHighlight(bool highlight);

	int handleEvent(int event) override;
	void handleChildLeave() override;
};

class Img : public HTMLNode {
	std::unique_ptr<ImageBox> box;
	public:
	Img(std::shared_ptr<RootNode> root, std::shared_ptr<HTMLNode> parent, xmlpp::Node* const node);
	~Img() { box.release(); }

	void drawChildren(int& x, int& y, int& w, int& h) override;
};