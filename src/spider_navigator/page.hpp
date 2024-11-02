#pragma once

#include <FL/Fl_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_draw.H>
#include <FL/Fl_Menu_Bar.H>

#include <libxml++/libxml++.h>

#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

#include "tags.hpp"

class HTMLPage : public Fl_Group {
	void parseElement(xmlpp::Element* element);
	// void initNode(std::shared_ptr<HTMLNode> node);
	
	// void measureAndDraw();

	// void measureChildren(std::vector<std::unique_ptr<NodeStackInfo>>& queue, std::vector<std::unique_ptr<NodeStackInfo>>& drawStack);
	// void drawChildren(std::vector<std::unique_ptr<NodeStackInfo>>& drawStack);

	// bool getInteractiveFromPos(int x, int y, std::shared_ptr<HTMLNode>& out);

	// int hoverRendered();
	// int clickRendered();
	
	protected:
	int cursor_x = 0;
	int cursor_y = 0;
	int padding = 0;

	// Store the previous children's height.
	int height_buffer = 0;
	
	int current_hovered = -1;
	
	// void draw();

	// int handle(int event);
	public:

	HTMLPage(xmlpp::Element* body_root, int x, int y, int w, int h, int horizontal_padding);
	
	void getCursor(int& outX, int& outY) { outX = cursor_x; outY = cursor_y; }
	void setCursor(int inX, int inY) { cursor_x = inX; cursor_y = inY; }

	void setHovered(int hover_id) { current_hovered = hover_id; }
	int getHovered() const { return current_hovered; }

	int getHeightBuffer() const { return height_buffer; }
	void setHeightBuffer(int height) { height_buffer = height; }
	
	int x() { return padding; }
	// int w() { 
	// 	int par_width = parent_window->w();
	// 	return (par_width - (padding * 3)); 
	// }
};