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
		std::shared_ptr<HTMLNode>(&text_3),
	},
	{
	},
};
HTMLNode body_2 = HTMLNode {
	"",
	{
		std::shared_ptr<HTMLNode>(&p_3),
	},
	{
		{"title", "The Scream"},
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
CoolMythsScreamHTMLWindow::CoolMythsScreamHTMLWindow(int x, int y, int w, int h) : HTMLWindow(std::shared_ptr<HTMLNode>(&CoolMythsScreamHTMLWindowNamespace::html_1), x, y, w, h) {

}
