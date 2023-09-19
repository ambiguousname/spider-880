#pragma once

#include <FL/Fl_Window.H>
#include <memory>
#include <vector>
#include <unordered_map>
#include <FL/Fl_Scroll.H>

using namespace std;

enum NodeType {
	DEFAULT,
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

class HTMLPage : public Fl_Group {
	void drawChildren();
	
	protected:
	shared_ptr<HTMLNode> root = nullptr;
	public:
	HTMLPage(shared_ptr<HTMLNode> root, int x, int y, int w, int h);

	virtual void draw();
};

class HTMLWindow : public Fl_Window {
	void drawChildren();

	HTMLPage* page;
	Fl_Scroll* scrollbar;
	public:
	HTMLWindow(shared_ptr<HTMLNode> root, int x, int y, int w, int h);
};