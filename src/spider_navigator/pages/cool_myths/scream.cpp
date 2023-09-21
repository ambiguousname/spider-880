#include "pages.h"
const Text text_3 = {
	"Scream all you want. No one will hear you.",
	{
	},
	{
	},
};
const P p_3 = {
	"",
	{
		make_shared<HTMLNode>(text_3),
	},
	{
	},
};
const HTMLNode body_2 = {
	"",
	{
		make_shared<HTMLNode>(p_3),
	},
	{
		{"title", "The Scream"},
	},
};
const HTMLNode html_1 = {
	"",
	{
		make_shared<HTMLNode>(body_2),
	},
	{
	},
};
CoolMythsScreamHTMLWindow::CoolMythsScreamHTMLWindow(int x, int y, int w, int h) : HTMLWindow(make_shared<HTMLNode>(html_1), x, y, w, h) {

}
