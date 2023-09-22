#include "scream.h"
namespace CoolMythsScreamHTMLWindowNamespace {
Text text_3 = Text {
	"Scream all you want. No one will hear you.",
	{
	},
	{
	},
};
P p_3 = P {
	"",
	{
		std::make_shared<HTMLNode>(text_3),
	},
	{
	},
};
HTMLNode body_2 = HTMLNode {
	"",
	{
		std::make_shared<HTMLNode>(p_3),
	},
	{
		{"title", "The Scream"},
	},
};
HTMLNode html_1 = HTMLNode {
	"",
	{
		std::make_shared<HTMLNode>(body_2),
	},
	{
	},
};
}
CoolMythsScreamHTMLWindow::CoolMythsScreamHTMLWindow(int x, int y, int w, int h) : HTMLWindow(std::make_shared<HTMLNode>(CoolMythsScreamHTMLWindowNamespace::html_1), x, y, w, h) {

}
