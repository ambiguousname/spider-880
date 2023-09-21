#pragma once

#include "tags.h"
#include <FL/Fl_Window.H>
#include <FL/Fl_Scroll.H>
#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class HTMLPage;
class HTMLWindow;

enum NodeQueueInfoEnum {
	OPEN_NODE,
	CLOSE_NODE
};

struct NodeQueueInfo {
	HTMLNodePtr node;
	NodeQueueInfoEnum type;
};

class HTMLPage : public Fl_Group {
	void initNode(HTMLNodePtr node);
	void drawChildren();

	bool getInteractiveFromPos(int x, int y, HTMLNodePtr out);

	int hoverRendered();
	int clickRendered();
	
	protected:
	int cursor_x = 0;
	int cursor_y = 0;
	int height_buffer = 0;


	shared_ptr<HTMLNode> root = nullptr;

	vector<shared_ptr<HTMLNode>> interactive_nodes;
	
	virtual void draw();

	int handle(int event);
	public:
	const shared_ptr<HTMLWindow> parent_window;
	HTMLPage(shared_ptr<HTMLNode> root, shared_ptr<HTMLWindow> parent, int x, int y, int w, int h);
	void getCursor(int& outX, int& outY) { outX = cursor_x; outY = cursor_y; }
	void setCursor(int inX, int inY) { cursor_x = inX; cursor_y = inY; }
};


// Mostly for storing an HTML page. Might put some browser looking things (search bar?) on the top.
// TODO: When an HTMLWindow is constructed from a root node, it returns a shared pointer 
// May not pose a problem right now, but what if we need to make multiple windows of the same page that show different information?
// Mayhaps some copying is in order in the future.
class HTMLWindow : public Fl_Window {
	void drawChildren();

	HTMLPage* page;
	Fl_Scroll* scrollbar;
	protected:
	// Other HTML pages (or just FL_Windows) linked by <a> tags.
	unordered_map<string, function<HTMLWindow*(int, int, int, int)>> linked_windows;

	public:
	HTMLWindow(shared_ptr<HTMLNode> root, int x, int y, int w, int h);

	bool getLinkedWindow(string name, function<HTMLWindow*(int, int, int, int)> &out);
};
typedef function<HTMLWindow*(int, int, int, int)> windowCreation; 