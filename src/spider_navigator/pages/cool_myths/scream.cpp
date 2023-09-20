#include "pages.h"
const HTMLNode text_3 = {
	TEXT,
	"Scream all you want. No one will hear you.",
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
const HTMLNode body_2 = {
	DEFAULT,
	"",
	{
		make_shared<HTMLNode>(p_3),
	},
	{
		{"title", "The Scream"},
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
CoolMythsScreamHTMLWindow::CoolMythsScreamHTMLWindow(int x, int y, int w, int h) : HTMLWindow(make_shared<HTMLNode>(html_1), x, y, w, h) {
	linked_windows = {};
}
HTMLWindow* CoolMythsScreamHTMLWindow::createWindow(int x, int y, int w, int h) {
	 return new CoolMythsScreamHTMLWindow(x, y, w, h);
}
