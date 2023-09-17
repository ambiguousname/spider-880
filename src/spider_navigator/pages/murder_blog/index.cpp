#include "pages.h"
namespace MurderBlogIndexHTMLPage {	
	void onStart() {
		std::cout << "Hello world!";
	}
		
	void draw() {
		Fl_Window *window = new Fl_Window(0, 0, 300, 300, "My Blog (GEANE: CHANGE TITLE TEXT)");
		Fl_Text_Display *p_6 = new Fl_Text_Display(0, 0, 300, 300);
		p_6->box(FL_NO_BOX);
		Fl_Text_Buffer *p_6_text = new Fl_Text_Buffer();
		Fl_Text_Buffer *p_6_style = new Fl_Text_Buffer();
		p_6->buffer(p_6_text);
		p_6_text->append("Image courtesy of ");
		p_6_style->append("AAAAAAAAAAAAAAAAAA");
		Fl_Text_Display::Style_Table_Entry p_6_style_table[] = {
			 { FL_FOREGROUND_COLOR, FL_COURIER, 16 },
		};
		p_6->highlight_data(p_6_style, p_6_style_table, 1, 'A', 0, 0);
		p_6->wrap_mode(3, 0);
		Fl_Text_Display *p_8 = new Fl_Text_Display(0, 0, 300, 300);
		p_8->box(FL_NO_BOX);
		Fl_Text_Buffer *p_8_text = new Fl_Text_Buffer();
		Fl_Text_Buffer *p_8_style = new Fl_Text_Buffer();
		p_8->buffer(p_8_text);
		p_8_text->append("The adage holds true. I've been getting too many \"customer complaints\" in my spam box to say it again, but just imagine my words now.");
		p_8_style->append("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		Fl_Text_Display::Style_Table_Entry p_8_style_table[] = {
			 { FL_FOREGROUND_COLOR, FL_COURIER, 16 },
		};
		p_8->highlight_data(p_8_style, p_8_style_table, 1, 'A', 0, 0);
		p_8->wrap_mode(3, 0);
		Fl_Text_Display *p_9 = new Fl_Text_Display(0, 0, 300, 300);
		p_9->box(FL_NO_BOX);
		Fl_Text_Buffer *p_9_text = new Fl_Text_Buffer();
		Fl_Text_Buffer *p_9_style = new Fl_Text_Buffer();
		p_9->buffer(p_9_text);
		p_9_text->append("In case I happen to shock and/or surprise any of the slow-witted among you. ");
		p_9_style->append("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		p_9_text->append("is a ");
		p_9_style->append("AAAAA");
		p_9_text->append(". I just pray that you're not as stupid as everyone makes you out to be. ");
		p_9_style->append("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		Fl_Text_Display::Style_Table_Entry p_9_style_table[] = {
			 { FL_FOREGROUND_COLOR, FL_COURIER, 16 },
		};
		p_9->highlight_data(p_9_style, p_9_style_table, 1, 'A', 0, 0);
		p_9->wrap_mode(3, 0);
		Fl_Text_Display *p_13 = new Fl_Text_Display(0, 0, 300, 300);
		p_13->box(FL_NO_BOX);
		Fl_Text_Buffer *p_13_text = new Fl_Text_Buffer();
		Fl_Text_Buffer *p_13_style = new Fl_Text_Buffer();
		p_13->buffer(p_13_text);
		p_13_text->append("Details as I can get them are scarce. Police aren't saying much other than that the body was found in the abandoned caves by Rorik End's scenic, beautiful, tourist-attracting, all around pleasant space, Garbage Park.");
		p_13_style->append("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		Fl_Text_Display::Style_Table_Entry p_13_style_table[] = {
			 { FL_FOREGROUND_COLOR, FL_COURIER, 16 },
		};
		p_13->highlight_data(p_13_style, p_13_style_table, 1, 'A', 0, 0);
		p_13->wrap_mode(3, 0);
		Fl_Text_Display *p_14 = new Fl_Text_Display(0, 0, 300, 300);
		p_14->box(FL_NO_BOX);
		Fl_Text_Buffer *p_14_text = new Fl_Text_Buffer();
		Fl_Text_Buffer *p_14_style = new Fl_Text_Buffer();
		p_14->buffer(p_14_text);
		p_14_text->append("I want all the viewers at home to know that I am not heartless. In fact, the more I stare at the blood and sinews and guts leaking out of this poor fellow, the more I am completely unnerved. I guess with 24-bit colors you can really see the whole enchilada.");
		p_14_style->append("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		Fl_Text_Display::Style_Table_Entry p_14_style_table[] = {
			 { FL_FOREGROUND_COLOR, FL_COURIER, 16 },
		};
		p_14->highlight_data(p_14_style, p_14_style_table, 1, 'A', 0, 0);
		p_14->wrap_mode(3, 0);
		Fl_Text_Display *p_15 = new Fl_Text_Display(0, 0, 300, 300);
		p_15->box(FL_NO_BOX);
		Fl_Text_Buffer *p_15_text = new Fl_Text_Buffer();
		Fl_Text_Buffer *p_15_style = new Fl_Text_Buffer();
		p_15->buffer(p_15_text);
		p_15_text->append("Corpses typically don't float. Speaking as an expert in murder (with a focus in fluid dynamics), they don't float unless they weigh less than the fluid they are displacing. That's a little scientific thing called the Archimedes Principle, and it doesn't allow for violations. For any of you wondering if the corpse is floating because of the stalactite protruding through the chest: no.");
		p_15_style->append("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		Fl_Text_Display::Style_Table_Entry p_15_style_table[] = {
			 { FL_FOREGROUND_COLOR, FL_COURIER, 16 },
		};
		p_15->highlight_data(p_15_style, p_15_style_table, 1, 'A', 0, 0);
		p_15->wrap_mode(3, 0);
		Fl_Text_Display *p_16 = new Fl_Text_Display(0, 0, 300, 300);
		p_16->box(FL_NO_BOX);
		Fl_Text_Buffer *p_16_text = new Fl_Text_Buffer();
		Fl_Text_Buffer *p_16_style = new Fl_Text_Buffer();
		p_16->buffer(p_16_text);
		p_16_text->append("The friction of the organs on the stalactite is too weak compared to the force of gravity. So we should be sinking down. And instead our remains trapped in the fluid. Just like when I shoved Jim's dog in the lake.");
		p_16_style->append("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		Fl_Text_Display::Style_Table_Entry p_16_style_table[] = {
			 { FL_FOREGROUND_COLOR, FL_COURIER, 16 },
		};
		p_16->highlight_data(p_16_style, p_16_style_table, 1, 'A', 0, 0);
		p_16->wrap_mode(3, 0);
		Fl_Text_Display *p_17 = new Fl_Text_Display(0, 0, 300, 300);
		p_17->box(FL_NO_BOX);
		Fl_Text_Buffer *p_17_text = new Fl_Text_Buffer();
		Fl_Text_Buffer *p_17_style = new Fl_Text_Buffer();
		p_17->buffer(p_17_text);
		p_17_text->append("To all of the loud-mouthed Rorikenders I know: shut your gagging SPNPOLICY200 flaps. And remember to stay safe out there.");
		p_17_style->append("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		Fl_Text_Display::Style_Table_Entry p_17_style_table[] = {
			 { FL_FOREGROUND_COLOR, FL_COURIER, 16 },
		};
		p_17->highlight_data(p_17_style, p_17_style_table, 1, 'A', 0, 0);
		p_17->wrap_mode(3, 0);
		window->end();
		window->resizable(*window);
		window->show();
		onStart();
	Fl::run();
	}
}