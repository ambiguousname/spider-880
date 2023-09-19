#include "pages.h"
void onStart() {}
const HTMLNode p_3 = {
	"p",
	"Scream all you want. No one will hear you.",
	make_shared<HTMLNode>(body_2),
	{
	},
	{
	},
};
const HTMLNode body_2 = {
	"body",
	"",
	make_shared<HTMLNode>(html_1),
	{
		make_shared<HTMLNode>(p_3),
	},
	{
		{"title", "The Scream"},
	},
};
const HTMLNode html_1 = {
	"html",
	"",
nullptr,
	{
		make_shared<HTMLNode>(body_2),
	},
	{
	},
};
CoolMythsScreamHTMLPage::CoolMythsScreamHTMLPage(int x, int y, int w, int h) : HTMLPage(make_shared<HTMLNode>(page), x, y, w, h) {

}