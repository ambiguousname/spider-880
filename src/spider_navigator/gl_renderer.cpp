#include "gl_renderer.h"

HTMLGLRender::HTMLGLRender(int x, int y, int w, int h, const char* title) : Fl_Gl_Window(x, y, w, h, title) {
	end();
	show();
	clear_border();
}