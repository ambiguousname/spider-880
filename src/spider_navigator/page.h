#pragma once

#include <FL/Fl_Window.H>
#include <memory>
#include <vector>
#include <unordered_map>

using namespace std;

struct HTMLNode {
	const char* tag_name;
	const char* data;
	const vector<shared_ptr<HTMLNode>> children;
	const unordered_map<const char*, const char*> attributes;
};

typedef shared_ptr<HTMLNode> HTMLNodePtr;

class HTMLPage : public Fl_Window {
	void drawChildren(shared_ptr<HTMLNode> node);
	protected:
	shared_ptr<HTMLNode> root = nullptr;
	public:
	HTMLPage(shared_ptr<HTMLNode> root, int x, int y, int w, int h);

	virtual void draw();
};