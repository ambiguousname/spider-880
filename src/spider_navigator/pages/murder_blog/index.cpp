#include "pages.h"
const HTMLNode header_3 = {
	DEFAULT,
	"",
	{
	},
	{
	},
};
const HTMLNode text_6 = {
	TEXT,
	"			Image courtesy of ",
	{
	},
	{
	},
};
const HTMLNode text_8 = {
	TEXT,
	"user:engounge",
	{
	},
	{
	},
};
const HTMLNode a_8 = {
	A,
	"",
	{
		make_shared<HTMLNode>(text_8),
	},
	{
	},
};
const HTMLNode text_9 = {
	TEXT,
	".		",
	{
	},
	{
	},
};
const HTMLNode p_6 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_9),
		make_shared<HTMLNode>(a_8),
		make_shared<HTMLNode>(text_6),
	},
	{
	},
};
const HTMLNode text_11 = {
	TEXT,
	"			The adage holds true. I've been getting too many \"customer complaints\" in my spam box to say it again, but just imagine my words now.		",
	{
	},
	{
	},
};
const HTMLNode p_11 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_11),
	},
	{
	},
};
const HTMLNode text_13 = {
	TEXT,
	"			In case I happen to shock and/or surprise any of the slow-witted among you. ",
	{
	},
	{
	},
};
const HTMLNode text_15 = {
	TEXT,
	"Rorik's",
	{
	},
	{
	},
};
const HTMLNode a_15 = {
	A,
	"",
	{
		make_shared<HTMLNode>(text_15),
	},
	{
	},
};
const HTMLNode text_17 = {
	TEXT,
	"End",
	{
	},
	{
	},
};
const HTMLNode a_17 = {
	A,
	"",
	{
		make_shared<HTMLNode>(text_17),
	},
	{
	},
};
const HTMLNode text_18 = {
	TEXT,
	" is a ",
	{
	},
	{
	},
};
const HTMLNode text_20 = {
	TEXT,
	"SPNPOLICY200",
	{
	},
	{
	},
};
const HTMLNode a_20 = {
	A,
	"",
	{
		make_shared<HTMLNode>(text_20),
	},
	{
	},
};
const HTMLNode text_21 = {
	TEXT,
	". I just pray that you're not as stupid as everyone makes you out to be. 		",
	{
	},
	{
	},
};
const HTMLNode p_13 = {
	P,
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
const HTMLNode text_23 = {
	TEXT,
	"			Details as I can get them are scarce. Police aren't saying much other than that the body was found in the abandoned caves by Rorik End's scenic, beautiful, tourist-attracting, all around pleasant space, Egg Park.		",
	{
	},
	{
	},
};
const HTMLNode p_23 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_23),
	},
	{
	},
};
const HTMLNode text_25 = {
	TEXT,
	"			I want all the viewers at home to know that I am not heartless. In fact, the more I stare at the blood and sinews and guts leaking out of this poor fellow, the more I am completely unnerved. I guess with 24-bit colors you can really see the whole enchilada.		",
	{
	},
	{
	},
};
const HTMLNode p_25 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_25),
	},
	{
	},
};
const HTMLNode text_27 = {
	TEXT,
	"			Corpses typically don't float. Speaking as an expert in murder (with a focus in fluid dynamics), they don't float unless they weigh less than the fluid they are displacing. That's a little scientific thing called the Archimedes Principle, and it doesn't allow for violations. For any of you wondering if the corpse is floating because of the stalactite protruding through the chest: no.		",
	{
	},
	{
	},
};
const HTMLNode p_27 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_27),
	},
	{
	},
};
const HTMLNode text_29 = {
	TEXT,
	"			The friction of the organs on the stalactite is too weak compared to the force of gravity. So we should be sinking down. And instead our remains trapped in the fluid. Just like when I shoved Jim's dog in the lake.		",
	{
	},
	{
	},
};
const HTMLNode p_29 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_29),
	},
	{
	},
};
const HTMLNode text_31 = {
	TEXT,
	"			To all of the loud-mouthed Rorikenders I know: shut your gagging SPNPOLICY200 flaps. And remember to stay safe out there.		",
	{
	},
	{
	},
};
const HTMLNode p_31 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_31),
	},
	{
	},
};
const HTMLNode body_5 = {
	DEFAULT,
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
		{"title", "My Blog (GEANE: CHANGE TITLE TEXT)"},
		{"w", "300"},
		{"h", "300"},
	},
};
const HTMLNode html_1 = {
	DEFAULT,
	"",
	{
		make_shared<HTMLNode>(body_5),
		make_shared<HTMLNode>(header_3),
	},
	{
	},
};
MurderBlogIndexHTMLWindow::MurderBlogIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(make_shared<HTMLNode>(html_1), x, y, w, h) {

}