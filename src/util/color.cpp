#include "color.hpp"
#include <math.h>
#include <FL/Fl.H>

const Fl_Color PALETTE[16] = {0x00000000, 0xff000000, 0x00ff0000, 0xffff0000, 0x0000ff00, 0xff00ff00, 0x00ffff00, 0xffffff00, 0x555555, FL_DARK_RED, 9, 10, 11, 12, 13, 14}; 

Fl_Color rgb_to_palette(unsigned char r, unsigned char g, unsigned char b) {
	int len = sizeof(PALETTE)/sizeof(Fl_Color);

	double closest_dist = INFINITY;
	Fl_Color closest_color = 0;
	for (int i = 0; i < len; i++) {
		Fl_Color color = PALETTE[i];
		
		
		unsigned char c_r, c_g, c_b;

		Fl::get_color(color, c_r, c_g, c_b);

		double r_dist = pow(r - c_r, 2);
		double g_dist = pow(g - c_g, 2);
		double b_dist = pow(b - c_b, 2);

		double dist = sqrt(r_dist + g_dist + b_dist);

		if (dist < closest_dist) {
			closest_dist = dist;
			closest_color = color;
		}
	}
	return closest_color;
}