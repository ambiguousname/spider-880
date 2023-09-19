#include "pages.h"
const HTMLNode p_3 = {
	"p",
	"As a native of Rorik's End myself, there's a somewhat buried tale about Rorik Andersen himself that I think deserves attention. It comes from his grandniece (on his wife's side): Eliza Anderson's \"History of the Andersens\" (1962). I've excerpted the relevant portions here, but for contex the story itself takes place after he filed for bankruptcy and sold Andersen Mining:",
	{
	},
	{
	},
};
const HTMLNode p_4 = {
	"p",
	"What follows is an amalgamation of records of speculation from local sources (mostly rumor mills), and my grandmother's own recollection of what her brother-in-law said at the time.",
	{
	},
	{
	},
};
const HTMLNode p_5 = {
	"p",
	"Rorik decided to walk home after a long day in court, and for whatever reason decided to make a detour. He recalled swinging by the Emerald Meadows (colloquially known as Egg Park), and encountering a man with an apparently long coat.",
	{
	},
	{
	},
};
const HTMLNode p_6 = {
	"p",
	"The man asks Rorik what he's doing there.",
	{
	},
	{
	},
};
const HTMLNode p_7 = {
	"p",
	"\"I own this park. Haven't you heard of me?\"",
	{
	},
	{
	},
};
const HTMLNode p_8 = {
	"p",
	"The man says he has. But he says it's not Rorik's park, and something to the effect that it belongs to the city.",
	{
	},
	{
	},
};
const HTMLNode p_9 = {
	"p",
	"\"Show some respect for your betters.\"",
	{
	},
	{
	},
};
const HTMLNode p_10 = {
	"p",
	"The man assaults Rorik, and there's a scuffle. Rorik shows up to the police station about an hour later, very beaten and bruised. He claims to have driven the other man off, and eventually returns home.",
	{
	},
	{
	},
};
const HTMLNode p_11 = {
	"p",
	"The next day, Rorik orders newspapers to run a front-page piece the next day, the headline reading: \"Death to Traitors\".",
	{
	},
	{
	},
};
const HTMLNode p_12 = {
	"p",
	"The content of the article is a matter of public record, and one I will not repeat here.",
	{
	},
	{
	},
};
const HTMLNode p_13 = {
	"p",
	"What was not in the public record, is my grandmother's sole recollection of Rorik's behavior on the night in question. He apparently called my grandmother to let her know that our family was to be disinherited.",
	{
	},
	{
	},
};
const HTMLNode p_14 = {
	"p",
	"TODO:",
	{
	},
	{
	},
};
const HTMLNode p_15 = {
	"p",
	"Rorik was found dead 3 weeks later, ruled a suicide.",
	{
	},
	{
	},
};
const HTMLNode body_2 = {
	"body",
	"",
	{
		make_shared<HTMLNode>(p_3),
		make_shared<HTMLNode>(p_4),
		make_shared<HTMLNode>(p_5),
		make_shared<HTMLNode>(p_6),
		make_shared<HTMLNode>(p_7),
		make_shared<HTMLNode>(p_8),
		make_shared<HTMLNode>(p_9),
		make_shared<HTMLNode>(p_10),
		make_shared<HTMLNode>(p_11),
		make_shared<HTMLNode>(p_12),
		make_shared<HTMLNode>(p_13),
		make_shared<HTMLNode>(p_14),
		make_shared<HTMLNode>(p_15),
	},
	{
		{"title", "The End"},
	},
};
const HTMLNode html_1 = {
	"html",
	"",
	{
		make_shared<HTMLNode>(body_2),
	},
	{
	},
};
CoolMythsTheendHTMLPage::CoolMythsTheendHTMLPage(int x, int y, int w, int h) : HTMLPage(make_shared<HTMLNode>(html_1), x, y, w, h) {

}