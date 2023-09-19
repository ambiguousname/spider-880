#include "pages.h"
const HTMLNode header_3 = {
	DEFAULT,
	"",
	{
	},
	{
	},
};
void onStart() {
	std::cout << "Hello world!";
}
const HTMLNode a_7 = {
	A,
	"user:engounge",
	{
	},
	{
	},
};
const HTMLNode p_6 = {
	P,
	"Image courtesy of ",
	{
		make_shared<HTMLNode>(a_7),
	},
	{
	},
};
const HTMLNode p_8 = {
	P,
	"The adage holds true. I've been getting too many \"customer complaints\" in my spam box to say it again, but just imagine my words now.",
	{
	},
	{
	},
};
const HTMLNode a_10 = {
	A,
	"Rorik",
	{
	},
	{
	},
};
const HTMLNode a_11 = {
	A,
	"End",
	{
	},
	{
	},
};
const HTMLNode a_12 = {
	A,
	"SPNPOLICY200",
	{
	},
	{
	},
};
const HTMLNode p_9 = {
	P,
	"In case I happen to shock and/or surprise any of the slow-witted among you. is a . I just pray that you're not as stupid as everyone makes you out to be. ",
	{
		make_shared<HTMLNode>(a_10),
		make_shared<HTMLNode>(a_11),
		make_shared<HTMLNode>(a_12),
	},
	{
	},
};
const HTMLNode p_13 = {
	P,
	"Details as I can get them are scarce. Police aren't saying much other than that the body was found in the abandoned caves by Rorik End's scenic, beautiful, tourist-attracting, all around pleasant space, Egg Park.",
	{
	},
	{
	},
};
const HTMLNode p_14 = {
	P,
	"I want all the viewers at home to know that I am not heartless. In fact, the more I stare at the blood and sinews and guts leaking out of this poor fellow, the more I am completely unnerved. I guess with 24-bit colors you can really see the whole enchilada.",
	{
	},
	{
	},
};
const HTMLNode p_15 = {
	P,
	"Corpses typically don't float. Speaking as an expert in murder (with a focus in fluid dynamics), they don't float unless they weigh less than the fluid they are displacing. That's a little scientific thing called the Archimedes Principle, and it doesn't allow for violations. For any of you wondering if the corpse is floating because of the stalactite protruding through the chest: no.",
	{
	},
	{
	},
};
const HTMLNode p_16 = {
	P,
	"The friction of the organs on the stalactite is too weak compared to the force of gravity. So we should be sinking down. And instead our remains trapped in the fluid. Just like when I shoved Jim's dog in the lake.",
	{
	},
	{
	},
};
const HTMLNode p_17 = {
	P,
	"To all of the loud-mouthed Rorikenders I know: shut your gagging SPNPOLICY200 flaps. And remember to stay safe out there.",
	{
	},
	{
	},
};
const HTMLNode body_5 = {
	DEFAULT,
	"",
	{
		make_shared<HTMLNode>(p_6),
		make_shared<HTMLNode>(p_8),
		make_shared<HTMLNode>(p_9),
		make_shared<HTMLNode>(p_13),
		make_shared<HTMLNode>(p_14),
		make_shared<HTMLNode>(p_15),
		make_shared<HTMLNode>(p_16),
		make_shared<HTMLNode>(p_17),
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
		make_shared<HTMLNode>(header_3),
		make_shared<HTMLNode>(body_5),
	},
	{
	},
};
MurderBlogIndexHTMLPage::MurderBlogIndexHTMLPage(int x, int y, int w, int h) : HTMLPage(make_shared<HTMLNode>(html_1), x, y, w, h) {

}