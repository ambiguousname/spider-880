#include "pages.h"
namespace MurderBlogIndexHTMLPage {	
	void onStart() {
		std::cout << "Hello world!";
	}
		
	void draw() {
		Fl_Window *window = new Fl_Window(0, 0, 300, 300, "My Blog (GEANE: CHANGE TITLE TEXT)");
		ImageBox *img_6 = new ImageBox("./assets/test.png", 0, 0, 100, 100);
		Fl_Box *p_7 = new Fl_Box(0, 0, 300, 300);
		p_7->label("			Image courtesy of ");
		p_7->label("		");
		Fl_Box *p_9 = new Fl_Box(0, 0, 300, 300);
		p_9->label("			The adage holds true. I've been getting too many \"customer complaints\" in my spam box to say it again, but just imagine my words now.		");
		Fl_Box *p_10 = new Fl_Box(0, 0, 300, 300);
		p_10->label("			In case I happen to shock and/or surprise any of the slow-witted among you. ");
		p_10->label(" ");
		p_10->label(" is a ");
		p_10->label(". I just pray that you're not as stupid as everyone makes you out to be. 		");
		Fl_Box *p_14 = new Fl_Box(0, 0, 300, 300);
		p_14->label("			Details as I can get them are scarce. Police aren't saying much other than that the body was found in the abandoned caves by Rorik End's scenic, beautiful, tourist-attracting, all around pleasant space, Garbage Park.		");
		Fl_Box *p_15 = new Fl_Box(0, 0, 300, 300);
		p_15->label("			I want all the viewers at home to know that I am not heartless. In fact, the more I stare at the blood and sinews and guts leaking out of this poor fellow, the more I am completely unnerved. I guess with 24-bit colors you can really see the whole enchilada.		");
		Fl_Box *p_16 = new Fl_Box(0, 0, 300, 300);
		p_16->label("			Corpses typically don't float. Speaking as an expert in murder (with a focus in fluid dynamics), they don't float unless they weigh less than the fluid they are displacing. That's a little scientific thing called the Archimedes Principle, and it doesn't allow for violations. For any of you wondering if the corpse is floating because of the stalactite protruding through the chest: no.		");
		Fl_Box *p_17 = new Fl_Box(0, 0, 300, 300);
		p_17->label("			The friction of the organs on the stalactite is too weak compared to the force of gravity. So we should be sinking down. And instead our remains trapped in the fluid. Just like when I shoved Jim's dog in the lake.		");
		Fl_Box *p_18 = new Fl_Box(0, 0, 300, 300);
		p_18->label("			To all of the loud-mouthed Rorikenders I know: shut your gagging SPNPOLICY200 flaps. And remember to stay safe out there.		");
		Fl_Box *p_19 = new Fl_Box(0, 0, 300, 300);
		p_19->label("			Kurt Hawkins, Site Admin.		");
		window->end();
		window->show();
		onStart();
	}
}