#include "index.h"
namespace MurderBlogIndexHTMLWindowNamespace {
HTMLNode header_3 = HTMLNode {
	"",
	{
	},
	{
	},
};
Text text_6 = Text {
	"Image courtesy of ",
	{
	},
	{
	},
};
Text text_8 = Text {
	"user:engounge",
	{
	},
	{
	},
};
A a_8 = A {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_8),
	},
	{
	},
};
Text text_9 = Text {
	".",
	{
	},
	{
	},
};
P p_6 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_9),
		std::shared_ptr<HTMLNode>(&a_8),
		std::shared_ptr<HTMLNode>(&text_6),
	},
	{
	},
};
Text text_11 = Text {
	"The adage holds true. I've been getting too many \"customer complaints\" in my spam box to say it again, but just imagine my words now.",
	{
	},
	{
	},
};
P p_11 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_11),
	},
	{
	},
};
Text text_13 = Text {
	"In case I happen to shock and/or surprise any of the slow-witted among you. ",
	{
	},
	{
	},
};
Text text_15 = Text {
	"Rorik's ",
	{
	},
	{
	},
};
A a_15 = A {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_15),
	},
	{
	},
};
Text text_17 = Text {
	"End",
	{
	},
	{
		{"href", "cool_myths/theend"},
	},
};
A a_17 = A {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_17),
	},
	{
		{"href", "cool_myths/theend"},
	},
};
Text text_18 = Text {
	" is a ",
	{
	},
	{
	},
};
Text text_20 = Text {
	"SPNPOLICY200",
	{
	},
	{
	},
};
A a_20 = A {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_20),
	},
	{
	},
};
Text text_21 = Text {
	". I just pray that you're not as stupid as everyone makes you out to be. ",
	{
	},
	{
	},
};
P p_13 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_21),
		std::shared_ptr<HTMLNode>(&a_20),
		std::shared_ptr<HTMLNode>(&text_18),
		std::shared_ptr<HTMLNode>(&a_17),
		std::shared_ptr<HTMLNode>(&a_15),
		std::shared_ptr<HTMLNode>(&text_13),
	},
	{
	},
};
Text text_23 = Text {
	"Details as I can get them are scarce. Police aren't saying much other than that the body was found in the abandoned caves by Rorik End's scenic, beautiful, tourist-attracting, all around pleasant space, Egg Park.",
	{
	},
	{
	},
};
P p_23 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_23),
	},
	{
	},
};
Text text_25 = Text {
	"I want all the viewers at home to know that I am not heartless. In fact, the more I stare at the blood and sinews and guts leaking out of this poor fellow, the more I am completely unnerved. I guess with 24-bit colors you can really see the whole enchilada.",
	{
	},
	{
	},
};
P p_25 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_25),
	},
	{
	},
};
Text text_27 = Text {
	"Corpses typically don't float. Speaking as an expert in murder (with a focus in fluid dynamics), they don't float unless they weigh less than the fluid they are displacing. That's a little scientific thing called the Archimedes Principle, and it doesn't allow for violations. For any of you wondering if the corpse is floating because of the stalactite protruding through the chest: no.",
	{
	},
	{
	},
};
P p_27 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_27),
	},
	{
	},
};
Text text_29 = Text {
	"The friction of the organs on the stalactite is too weak compared to the force of gravity. So we should be sinking down. And instead our remains trapped in the fluid. Just like when I shoved Jim's dog in the lake.",
	{
	},
	{
	},
};
P p_29 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_29),
	},
	{
	},
};
Text text_31 = Text {
	"To all of the loud-mouthed Rorikenders I know: shut your gagging SPNPOLICY200 flaps. And remember to stay safe out there.",
	{
	},
	{
	},
};
P p_31 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_31),
	},
	{
	},
};
HTMLNode body_5 = HTMLNode {
	"",
	{
		std::shared_ptr<HTMLNode>(&p_31),
		std::shared_ptr<HTMLNode>(&p_29),
		std::shared_ptr<HTMLNode>(&p_27),
		std::shared_ptr<HTMLNode>(&p_25),
		std::shared_ptr<HTMLNode>(&p_23),
		std::shared_ptr<HTMLNode>(&p_13),
		std::shared_ptr<HTMLNode>(&p_11),
		std::shared_ptr<HTMLNode>(&p_6),
	},
	{
	},
};
HTMLNode html_1 = HTMLNode {
	"",
	{
		std::shared_ptr<HTMLNode>(&body_5),
		std::shared_ptr<HTMLNode>(&header_3),
	},
	{
		{"title", "My Blog (GEANE: CHANGE TITLE TEXT)"},
	},
};
}
MurderBlogIndexHTMLWindow::MurderBlogIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(std::shared_ptr<HTMLNode>(&MurderBlogIndexHTMLWindowNamespace::html_1), x, y, w, h) {
	linked_windows.insert({"cool_myths/theend", CoolMythsTheendHTMLWindow::createWindow});

}
