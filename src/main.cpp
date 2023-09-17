#include <FL/Fl.H>
#include <murder_blog/pages.h>

int main(int argc, char **argv) {
	MurderBlogIndexHTMLPage::draw();
	// return Fl::run();
	return 0;
}

/*

Fl_Text_Display *p_8 = new Fl_Text_Display(0, 0, 300, 300);

		// p_8->box(FL_NO_BOX);
		// p_8->wrap_mode(3, 0);
		Fl_Text_Buffer *p_8_text = new Fl_Text_Buffer();
		Fl_Text_Buffer *style_buffer = new Fl_Text_Buffer();
		Fl_Text_Display::Style_Table_Entry style_table[] = { 
			{  FL_RED,         FL_COURIER, 18 }, // A - Red
			{  FL_DARK_YELLOW, FL_COURIER, 18 },
		 };
		p_8->buffer(p_8_text);

		int num = sizeof(style_table)/sizeof(style_table[0]);
		p_8->highlight_data(style_buffer, style_table, num, 'A', 0, 0);

		p_8_text->text("Test");
		style_buffer->text("AABB");
*/