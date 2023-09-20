#include "color.h"
#include <math.h>
#include <FL/Fl.H>

const Fl_Color PALETTE[16] = {FL_BLACK, FL_RED, FL_GREEN, FL_YELLOW, FL_BLUE, FL_MAGENTA, FL_CYAN, FL_WHITE, FL_DARK_RED, FL_DARK_GREEN, FL_DARK_YELLOW, FL_DARK_BLUE, FL_DARK_MAGENTA, FL_DARK_CYAN, FL_DARK3, FL_DARK1}; 

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