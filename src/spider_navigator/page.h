#pragma once

#include <FL/Fl_Window.H>
#include <FL/Fl_Scroll.H>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

using namespace std;

enum NodeType {
	DEFAULT,
	TEXT,
	P,
	A,
	IMG,
};

struct HTMLNode {
	const NodeType tag;
	const char* data;
	const vector<shared_ptr<HTMLNode>> children;
	const unordered_map<string, string> attributes;
};

typedef shared_ptr<HTMLNode> HTMLNodePtr;

enum NodeQueueInfoEnum {
	OPEN_NODE,
	CLOSE_NODE
};

struct NodeQueueInfo {
	HTMLNodePtr node;
	HTMLNodePtr parent;
	NodeQueueInfoEnum type;
};

struct RenderedNode {
	int x;
	int y;
	int w;
	int h;
	NodeQueueInfo node_info;
	Fl_Cursor cursor;
};

class HTMLPage : public Fl_Group {
	void drawChildren();

	void closeNode(vector<NodeQueueInfo>& queue, NodeQueueInfo info);
	void openNode(vector<NodeQueueInfo>& queue, NodeQueueInfo info);

	bool getRenderedFromPos(int x, int y, RenderedNode& out);

	int hoverRendered();
	int clickRendered();
	
	protected:
	int cursor_x = 0;
	int cursor_y = 0;
	int height_buffer = 0;

	shared_ptr<HTMLNode> root = nullptr;

	// For clicking on stuff:
	vector<RenderedNode> rendered_nodes;
	
	virtual void draw();

	int handle(int event);
	public:
	HTMLPage(shared_ptr<HTMLNode> root, int x, int y, int w, int h);
};


class HTMLWindow : public Fl_Window {
	void drawChildren();

	HTMLPage* page;
	Fl_Scroll* scrollbar;
	protected:
	// Other HTML pages (or just FL_Windows) linked by <a> tags.
	vector<function<HTMLWindow*>> linked_windows;

	public:
	HTMLWindow(shared_ptr<HTMLNode> root, int x, int y, int w, int h);
};