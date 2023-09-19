#include "pages.h"
const HTMLNode p_3 = {
	P,
	"Scream all you want. No one will hear you.",
	{
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
CoolMythsScreamHTMLPage::CoolMythsScreamHTMLPage(int x, int y, int w, int h) : HTMLPage(make_shared<HTMLNode>(html_1), x, y, w, h) {

}