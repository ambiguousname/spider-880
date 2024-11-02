#pragma once

#include <FL/Fl_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_draw.H>
#include <FL/Fl_Menu_Bar.H>
#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include "tags.hpp"

class HTMLPage;
class HTMLWindow;
class HTMLNode;

enum NodeStackInfoEnum {
	OPEN_NODE,
	CLOSE_NODE
};

struct NodeStackInfo {
	std::shared_ptr<HTMLNode> node;
	NodeStackInfoEnum type;
	NodeStackInfo* parent_closer = nullptr;
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
};

// Because again, the nodes themselves as they exist are not unique across webpages.
struct InteractiveNode {
	std::shared_ptr<HTMLNode> node;
	int x;
	int y;
	int w;
	int h;
};

class HTMLPage : public Fl_Group {
	void initNode(std::shared_ptr<HTMLNode> node);
	
	void measureAndDraw();

	void measureChildren(std::vector<std::unique_ptr<NodeStackInfo>>& queue, std::vector<std::unique_ptr<NodeStackInfo>>& drawStack);
	void drawChildren(std::vector<std::unique_ptr<NodeStackInfo>>& drawStack);

	bool getInteractiveFromPos(int x, int y, std::shared_ptr<HTMLNode>& out);

	int hoverRendered();
	int clickRendered();
	
	protected:
	int cursor_x = 0;
	int cursor_y = 0;
	int padding = 0;

	// Store the previous children's height.
	int height_buffer = 0;
	
	int current_hovered = -1;


	std::shared_ptr<HTMLNode> root = nullptr;

	std::vector<InteractiveNode> interactive_nodes;
	
	void draw();

	int handle(int event);
	public:

	const std::shared_ptr<HTMLWindow> parent_window;
	HTMLPage(std::shared_ptr<HTMLNode> root, std::shared_ptr<HTMLWindow> parent, int x, int y, int w, int h, int horizontal_padding);
	
	void getCursor(int& outX, int& outY) { outX = cursor_x; outY = cursor_y; }
	void setCursor(int inX, int inY) { cursor_x = inX; cursor_y = inY; }

	void setHovered(int hover_id) { current_hovered = hover_id; }
	int getHovered() const { return current_hovered; }

	int getHeightBuffer() const { return height_buffer; }
	void setHeightBuffer(int height) { height_buffer = height; }
	
	int x() { return padding; }
	int w() { 
		int par_width = ((Fl_Window*)(parent_window.get()))->w();
		return (par_width - (padding * 3)); 
	}
};