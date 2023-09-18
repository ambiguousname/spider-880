#include "pages.h"
namespace CoolMythsScreamHTMLPage {
	void onStart() {}
	void draw() {
		Fl_Window *window = new Fl_Window(0, 0, 300, 300, "2");
		Fl_Text_Display *p_3 = new Fl_Text_Display(0, 0, 300, 300);
		p_3->box(FL_NO_BOX);
		Fl_Text_Buffer *p_3_text = new Fl_Text_Buffer();
		Fl_Text_Buffer *p_3_style = new Fl_Text_Buffer();
		p_3->buffer(p_3_text);
		p_3_text->append("Scream all you want. No one will hear you.");
		p_3_style->append("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		Fl_Text_Display::Style_Table_Entry p_3_style_table[] = {
			 { FL_FOREGROUND_COLOR, FL_COURIER, 16 },
		};
		p_3->highlight_data(p_3_style, p_3_style_table, 1, 'A', 0, 0);
		p_3->wrap_mode(3, 0);
		window->end();
		window->resizable(*window);
		window->show();
		onStart();
		Fl::run();
	}
}