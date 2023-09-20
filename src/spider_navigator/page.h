#pragma once

#include <FL/Fl_Window.H>
#include <FL/Fl_Scroll.H>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

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
	const unordered_map<const char*, const char*> attributes;
};

typedef shared_ptr<HTMLNode> HTMLNodePtr;

struct RenderedNode {
	int x;
	int y;
	int w;
	int h;
};

enum NodeQueueInfoEnum {
	OPEN_NODE,
	CLOSE_NODE
};

struct NodeQueueInfo {
	HTMLNodePtr node;
	NodeQueueInfoEnum type;
};

class HTMLPage : public Fl_Group {
	void drawChildren();

	void closeNode(vector<NodeQueueInfo>& queue, HTMLNodePtr node);
	void openNode(vector<NodeQueueInfo>& queue, HTMLNodePtr node);
	
	protected:
	int cursor_x = 0;
	int cursor_y = 0;
	int height_buffer = 0;

	shared_ptr<HTMLNode> root = nullptr;
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
	public:
	HTMLWindow(shared_ptr<HTMLNode> root, int x, int y, int w, int h);
};