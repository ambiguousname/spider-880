#include "pages.h"
namespace MurderBlogIndexHTMLPage {	
	void onStart() {
		std::cout << "Hello world!";
	}
		
	void draw() {
		Fl_Window *window = new Fl_Window(0, 0, 300, 300, "My Blog (GEANE: CHANGE TITLE TEXT)");
		Fl_Text_Display *p_6 = new Fl_Text_Display(0, 0, 300, 300);
		Fl_Text_Buffer *p_6_text = new Fl_Text_Buffer();
		p_6->buffer(p_6_text);
		p_6_text->append("Image courtesy of ");
		Fl_Text_Display *p_8 = new Fl_Text_Display(0, 0, 300, 300);
		Fl_Text_Buffer *p_8_text = new Fl_Text_Buffer();
		p_8->buffer(p_8_text);
		p_8_text->append("The adage holds true. I've been getting too many \"customer complaints\" in my spam box to say it again, but just imagine my words now.");
		Fl_Text_Display *p_9 = new Fl_Text_Display(0, 0, 300, 300);
		Fl_Text_Buffer *p_9_text = new Fl_Text_Buffer();
		p_9->buffer(p_9_text);
		p_9_text->append("In case I happen to shock and/or surprise any of the slow-witted among you. ");
		p_9_text->append("is a ");
		p_9_text->append(". I just pray that you're not as stupid as everyone makes you out to be. ");
		Fl_Text_Display *p_13 = new Fl_Text_Display(0, 0, 300, 300);
		Fl_Text_Buffer *p_13_text = new Fl_Text_Buffer();
		p_13->buffer(p_13_text);
		p_13_text->append("Details as I can get them are scarce. Police aren't saying much other than that the body was found in the abandoned caves by Rorik End's scenic, beautiful, tourist-attracting, all around pleasant space, Garbage Park.");
		Fl_Text_Display *p_14 = new Fl_Text_Display(0, 0, 300, 300);
		Fl_Text_Buffer *p_14_text = new Fl_Text_Buffer();
		p_14->buffer(p_14_text);
		p_14_text->append("I want all the viewers at home to know that I am not heartless. In fact, the more I stare at the blood and sinews and guts leaking out of this poor fellow, the more I am completely unnerved. I guess with 24-bit colors you can really see the whole enchilada.");
		Fl_Text_Display *p_15 = new Fl_Text_Display(0, 0, 300, 300);
		Fl_Text_Buffer *p_15_text = new Fl_Text_Buffer();
		p_15->buffer(p_15_text);
		p_15_text->append("Corpses typically don't float. Speaking as an expert in murder (with a focus in fluid dynamics), they don't float unless they weigh less than the fluid they are displacing. That's a little scientific thing called the Archimedes Principle, and it doesn't allow for violations. For any of you wondering if the corpse is floating because of the stalactite protruding through the chest: no.");
		Fl_Text_Display *p_16 = new Fl_Text_Display(0, 0, 300, 300);
		Fl_Text_Buffer *p_16_text = new Fl_Text_Buffer();
		p_16->buffer(p_16_text);
		p_16_text->append("The friction of the organs on the stalactite is too weak compared to the force of gravity. So we should be sinking down. And instead our remains trapped in the fluid. Just like when I shoved Jim's dog in the lake.");
		Fl_Text_Display *p_17 = new Fl_Text_Display(0, 0, 300, 300);
		Fl_Text_Buffer *p_17_text = new Fl_Text_Buffer();
		p_17->buffer(p_17_text);
		p_17_text->append("To all of the loud-mouthed Rorikenders I know: shut your gagging SPNPOLICY200 flaps. And remember to stay safe out there.");
		window->end();
		window->show();
		onStart();
	}
}