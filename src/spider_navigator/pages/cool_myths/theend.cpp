#include "theend.h"
namespace CoolMythsTheendHTMLWindowNamespace {
Text text_3 = Text {
	"As a native of Rorik's End myself, there's a somewhat buried tale about Rorik Andersen himself that I think deserves attention. It comes from his grandniece (on his wife's side): Eliza Anderson's \"History of the Andersens\" (1962). I've excerpted the relevant portions here, but for contex the story itself takes place after he filed for bankruptcy and sold Andersen Mining:",
	{
	},
	{
	},
};
P p_3 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_3),
	},
	{
	},
};
Text text_5 = Text {
	"What follows is an amalgamation of records of speculation from local sources (mostly rumor mills), and my grandmother's own recollection of what her brother-in-law said at the time.",
	{
	},
	{
	},
};
P p_5 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_5),
	},
	{
	},
};
Text text_7 = Text {
	"Rorik decided to walk home after a long day in court, and for whatever reason decided to make a detour. He recalled swinging by the Emerald Meadows (colloquially known as Egg Park), and encountering a man with an apparently long coat.",
	{
	},
	{
	},
};
P p_7 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_7),
	},
	{
	},
};
Text text_9 = Text {
	"The man asks Rorik what he's doing there.",
	{
	},
	{
	},
};
P p_9 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_9),
	},
	{
	},
};
Text text_11 = Text {
	"\"I own this park. Haven't you heard of me?\"",
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
	"The man says he has. But he says it's not Rorik's park, and something to the effect that it belongs to the city.",
	{
	},
	{
	},
};
P p_13 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_13),
	},
	{
	},
};
Text text_15 = Text {
	"\"Show some respect for your betters.\"",
	{
	},
	{
	},
};
P p_15 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_15),
	},
	{
	},
};
Text text_17 = Text {
	"The man assaults Rorik, and there's a scuffle. Rorik shows up to the police station about an hour later, very beaten and bruised. He claims to have driven the other man off, and eventually returns home.",
	{
	},
	{
	},
};
P p_17 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_17),
	},
	{
	},
};
Text text_19 = Text {
	"The next day, Rorik orders newspapers to run a front-page piece the next day, the headline reading: \"Death to Traitors\".",
	{
	},
	{
	},
};
P p_19 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_19),
	},
	{
	},
};
Text text_21 = Text {
	"The content of the article is a matter of public record, and one I will not repeat here.",
	{
	},
	{
	},
};
P p_21 = P {
	"",
	{
		std::shared_ptr<HTMLNode>(&text_21),
	},
	{
	},
};
Text text_23 = Text {
	"What was not in the public record, is my grandmother's sole recollection of Rorik's behavior on the night in question. He apparently called my grandmother to let her know that our family was to be disinherited.",
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
	"TODO:",
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
	"Rorik was found dead 3 weeks later, ruled a suicide.",
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
HTMLNode body_2 = HTMLNode {
	"",
	{
		std::shared_ptr<HTMLNode>(&p_27),
		std::shared_ptr<HTMLNode>(&p_25),
		std::shared_ptr<HTMLNode>(&p_23),
		std::shared_ptr<HTMLNode>(&p_21),
		std::shared_ptr<HTMLNode>(&p_19),
		std::shared_ptr<HTMLNode>(&p_17),
		std::shared_ptr<HTMLNode>(&p_15),
		std::shared_ptr<HTMLNode>(&p_13),
		std::shared_ptr<HTMLNode>(&p_11),
		std::shared_ptr<HTMLNode>(&p_9),
		std::shared_ptr<HTMLNode>(&p_7),
		std::shared_ptr<HTMLNode>(&p_5),
		std::shared_ptr<HTMLNode>(&p_3),
	},
	{
		{"title", "The End"},
	},
};
HTMLNode html_1 = HTMLNode {
	"",
	{
		std::shared_ptr<HTMLNode>(&body_2),
	},
	{
	},
};
}
CoolMythsTheendHTMLWindow::CoolMythsTheendHTMLWindow(int x, int y, int w, int h) : HTMLWindow(std::shared_ptr<HTMLNode>(&CoolMythsTheendHTMLWindowNamespace::html_1), x, y, w, h) {

}
