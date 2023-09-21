#include "pages.h"
const HTMLNode header_3 = {
	"",
	{
	},
	{
	},
};
const Text text_6 = {
	"Image courtesy of ",
	{
	},
	{
	},
};
const Text text_8 = {
	"user:engounge",
	{
	},
	{
	},
};
const HTMLNode a_8 = {
	"",
	{
		make_shared<HTMLNode>(text_8),
	},
	{
	},
};
const Text text_9 = {
	".",
	{
	},
	{
	},
};
const HTMLNode p_6 = {
	"",
	{
		make_shared<HTMLNode>(text_9),
		make_shared<HTMLNode>(a_8),
		make_shared<HTMLNode>(text_6),
	},
	{
	},
};
const Text text_11 = {
	"The adage holds true. I've been getting too many \"customer complaints\" in my spam box to say it again, but just imagine my words now.",
	{
	},
	{
	},
};
const HTMLNode p_11 = {
	"",
	{
		make_shared<HTMLNode>(text_11),
	},
	{
	},
};
const Text text_13 = {
	"In case I happen to shock and/or surprise any of the slow-witted among you. ",
	{
	},
	{
	},
};
const Text text_15 = {
	"Rorik's ",
	{
	},
	{
	},
};
const HTMLNode a_15 = {
	"",
	{
		make_shared<HTMLNode>(text_15),
	},
	{
	},
};
const Text text_17 = {
	"End",
	{
	},
	{
		{"href", "cool_myths/theend"},
	},
};
const HTMLNode a_17 = {
	"",
	{
		make_shared<HTMLNode>(text_17),
	},
	{
		{"href", "cool_myths/theend"},
	},
};
const Text text_18 = {
	" is a ",
	{
	},
	{
	},
};
const Text text_20 = {
	"SPNPOLICY200",
	{
	},
	{
	},
};
const HTMLNode a_20 = {
	"",
	{
		make_shared<HTMLNode>(text_20),
	},
	{
	},
};
const Text text_21 = {
	". I just pray that you're not as stupid as everyone makes you out to be. ",
	{
	},
	{
	},
};
const HTMLNode p_13 = {
	"",
	{
		make_shared<HTMLNode>(text_21),
		make_shared<HTMLNode>(a_20),
		make_shared<HTMLNode>(text_18),
		make_shared<HTMLNode>(a_17),
		make_shared<HTMLNode>(a_15),
		make_shared<HTMLNode>(text_13),
	},
	{
	},
};
const Text text_23 = {
	"Details as I can get them are scarce. Police aren't saying much other than that the body was found in the abandoned caves by Rorik End's scenic, beautiful, tourist-attracting, all around pleasant space, Egg Park.",
	{
	},
	{
	},
};
const HTMLNode p_23 = {
	"",
	{
		make_shared<HTMLNode>(text_23),
	},
	{
	},
};
const Text text_25 = {
	"I want all the viewers at home to know that I am not heartless. In fact, the more I stare at the blood and sinews and guts leaking out of this poor fellow, the more I am completely unnerved. I guess with 24-bit colors you can really see the whole enchilada.",
	{
	},
	{
	},
};
const HTMLNode p_25 = {
	"",
	{
		make_shared<HTMLNode>(text_25),
	},
	{
	},
};
const Text text_27 = {
	"Corpses typically don't float. Speaking as an expert in murder (with a focus in fluid dynamics), they don't float unless they weigh less than the fluid they are displacing. That's a little scientific thing called the Archimedes Principle, and it doesn't allow for violations. For any of you wondering if the corpse is floating because of the stalactite protruding through the chest: no.",
	{
	},
	{
	},
};
const HTMLNode p_27 = {
	"",
	{
		make_shared<HTMLNode>(text_27),
	},
	{
	},
};
const Text text_29 = {
	"The friction of the organs on the stalactite is too weak compared to the force of gravity. So we should be sinking down. And instead our remains trapped in the fluid. Just like when I shoved Jim's dog in the lake.",
	{
	},
	{
	},
};
const HTMLNode p_29 = {
	"",
	{
		make_shared<HTMLNode>(text_29),
	},
	{
	},
};
const Text text_31 = {
	"To all of the loud-mouthed Rorikenders I know: shut your gagging SPNPOLICY200 flaps. And remember to stay safe out there.",
	{
	},
	{
	},
};
const HTMLNode p_31 = {
	"",
	{
		make_shared<HTMLNode>(text_31),
	},
	{
	},
};
const HTMLNode body_5 = {
	"",
	{
		make_shared<HTMLNode>(p_31),
		make_shared<HTMLNode>(p_29),
		make_shared<HTMLNode>(p_27),
		make_shared<HTMLNode>(p_25),
		make_shared<HTMLNode>(p_23),
		make_shared<HTMLNode>(p_13),
		make_shared<HTMLNode>(p_11),
		make_shared<HTMLNode>(p_6),
	},
	{
	},
};
const HTMLNode html_1 = {
	"",
	{
		make_shared<HTMLNode>(body_5),
		make_shared<HTMLNode>(header_3),
	},
	{
		{"title", "My Blog (GEANE: CHANGE TITLE TEXT)"},
	},
};
MurderBlogIndexHTMLWindow::MurderBlogIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(make_shared<HTMLNode>(html_1), x, y, w, h) {
	linked_windows.insert({"cool_myths/theend", CoolMythsTheendHTMLWindow::createWindow});

}
