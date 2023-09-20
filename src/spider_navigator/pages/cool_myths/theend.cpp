#include "pages.h"
const HTMLNode text_3 = {
	TEXT,
	"As a native of Rorik's End myself, there's a somewhat buried tale about Rorik Andersen himself that I think deserves attention. It comes from his grandniece (on his wife's side): Eliza Anderson's \"History of the Andersens\" (1962). I've excerpted the relevant portions here, but for contex the story itself takes place after he filed for bankruptcy and sold Andersen Mining:",
	{
	},
	{
	},
};
const HTMLNode p_3 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_3),
	},
	{
	},
};
const HTMLNode text_5 = {
	TEXT,
	"What follows is an amalgamation of records of speculation from local sources (mostly rumor mills), and my grandmother's own recollection of what her brother-in-law said at the time.",
	{
	},
	{
	},
};
const HTMLNode p_5 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_5),
	},
	{
	},
};
const HTMLNode text_7 = {
	TEXT,
	"Rorik decided to walk home after a long day in court, and for whatever reason decided to make a detour. He recalled swinging by the Emerald Meadows (colloquially known as Egg Park), and encountering a man with an apparently long coat.",
	{
	},
	{
	},
};
const HTMLNode p_7 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_7),
	},
	{
	},
};
const HTMLNode text_9 = {
	TEXT,
	"The man asks Rorik what he's doing there.",
	{
	},
	{
	},
};
const HTMLNode p_9 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_9),
	},
	{
	},
};
const HTMLNode text_11 = {
	TEXT,
	"\"I own this park. Haven't you heard of me?\"",
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
	"The man says he has. But he says it's not Rorik's park, and something to the effect that it belongs to the city.",
	{
	},
	{
	},
};
const HTMLNode p_13 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_13),
	},
	{
	},
};
const HTMLNode text_15 = {
	TEXT,
	"\"Show some respect for your betters.\"",
	{
	},
	{
	},
};
const HTMLNode p_15 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_15),
	},
	{
	},
};
const HTMLNode text_17 = {
	TEXT,
	"The man assaults Rorik, and there's a scuffle. Rorik shows up to the police station about an hour later, very beaten and bruised. He claims to have driven the other man off, and eventually returns home.",
	{
	},
	{
	},
};
const HTMLNode p_17 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_17),
	},
	{
	},
};
const HTMLNode text_19 = {
	TEXT,
	"The next day, Rorik orders newspapers to run a front-page piece the next day, the headline reading: \"Death to Traitors\".",
	{
	},
	{
	},
};
const HTMLNode p_19 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_19),
	},
	{
	},
};
const HTMLNode text_21 = {
	TEXT,
	"The content of the article is a matter of public record, and one I will not repeat here.",
	{
	},
	{
	},
};
const HTMLNode p_21 = {
	P,
	"",
	{
		make_shared<HTMLNode>(text_21),
	},
	{
	},
};
const HTMLNode text_23 = {
	TEXT,
	"What was not in the public record, is my grandmother's sole recollection of Rorik's behavior on the night in question. He apparently called my grandmother to let her know that our family was to be disinherited.",
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
	"TODO:",
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
	"Rorik was found dead 3 weeks later, ruled a suicide.",
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
const HTMLNode body_2 = {
	DEFAULT,
	"",
	{
		make_shared<HTMLNode>(p_27),
		make_shared<HTMLNode>(p_25),
		make_shared<HTMLNode>(p_23),
		make_shared<HTMLNode>(p_21),
		make_shared<HTMLNode>(p_19),
		make_shared<HTMLNode>(p_17),
		make_shared<HTMLNode>(p_15),
		make_shared<HTMLNode>(p_13),
		make_shared<HTMLNode>(p_11),
		make_shared<HTMLNode>(p_9),
		make_shared<HTMLNode>(p_7),
		make_shared<HTMLNode>(p_5),
		make_shared<HTMLNode>(p_3),
	},
	{
		{"title", "The End"},
	},
};
const HTMLNode html_1 = {
	DEFAULT,
	"",
	{
		make_shared<HTMLNode>(body_2),
	},
	{
	},
};
CoolMythsTheendHTMLWindow::CoolMythsTheendHTMLWindow(int x, int y, int w, int h) : HTMLWindow(make_shared<HTMLNode>(html_1), x, y, w, h) {

}