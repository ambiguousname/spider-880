#include "pages.h"
void onStart() {}
const HTMLNode p_3 = {
	"p",
	"RORIK ANDERSEN was the only son of two loving parents. A descendant of Danish immigrants, his family came to the Americas in the 1690s as sugar plantation owners in the West Indies (now the Virgin Islands) and had held onto their land ever since. Rorik himself was born in 1826 to a thriving industry, with a booming economy and many happy workers.",
	make_shared<HTMLNode>(body_2),
	{
	},
	{
	},
};
const HTMLNode p_4 = {
	"p",
	"He took to his work diligently, improving the lives of himself, his family, and his workers. All was good for a time as he worked hard to provide for himself. Overseeing one of the nation's largest plantations was a lot of work.",
	make_shared<HTMLNode>(body_2),
	{
	},
	{
	},
};
const HTMLNode p_5 = {
	"p",
	"Things soured, as Rorik felt the cold grip of interference on his harvest. At the time he had taken up to writing Graham Waldorf, a fellow plantation owner in the Americas. In his correspondence, Rorik says: \"I am perplexed by the increasing demands of those defective in mind, body, and spirit to take up my burdens. None of the brigands insisting my dignity have struggled as I have in the higher duty to which I take.\" Rorik was upset by the devestation he saw in his country. He took with him his family and belongings on July 4th of 1848, and looked for greener pastures with his American comrades.",
	make_shared<HTMLNode>(body_2),
	{
	},
	{
	},
};
const HTMLNode p_6 = {
	"p",
	"It was a good thing too: Danish parliament sold the Virgin Islands to the U.S. 4 years later. But Rorik had lost much from the sudden move, and was eager to start again. He took a loan from his American friends, and set up another plantation in Louisiana. He worked doubly hard to ensure the prosperity of his lands.",
	make_shared<HTMLNode>(body_2),
	{
	},
	{
	},
};
const HTMLNode p_7 = {
	"p",
	"But not all was well. While most were welcoming of his new venture, there were some that would not accept him for his differences as a Danish immigrant. Rorik once wrote: \"My neighbors do not take kindly to my presence. I have managed to buy what land I could in further pursuit of my duty; they take this as an insult. I have resolved to not let their hearts temper my spirits. I sleep contented by the Kalthoff repeater resting by my bedside.\"",
	make_shared<HTMLNode>(body_2),
	{
	},
	{
	},
};
const HTMLNode p_8 = {
	"p",
	"Even with his determination tested, Rorik would see failure yet again: war came about 6 years into the founding of his new home. As Rorik puts it in another correspondence to Waldorf: \"The balance of my hearth is threatened by divisions on all sides. My crop is soured by foul weather and tempers alike.\"",
	make_shared<HTMLNode>(body_2),
	{
	},
	{
	},
};
const HTMLNode p_9 = {
	"p",
	"War came to the plantation, and Rorik found himself moving yet again. He was forced to move to desolate plains with hardly any of the wealth and status he had once held. Worse, he found the soil lacked any substantial nutrients that he could use to grow crops.",
	make_shared<HTMLNode>(body_2),
	{
	},
	{
	},
};
const HTMLNode p_10 = {
	"p",
	"But innovation would strike when he discovered coal while wandering the border of his new property. After boring into the earth to test the amount of suitable coal, Rorik found it to be plentiful. He got straight to work. ",
	make_shared<HTMLNode>(body_2),
	{
	},
	{
	},
};
const HTMLNode p_11 = {
	"p",
	"Within a few years, Rorik was able to use what meager resources he had left to hire laborers for a coal mine. From there, he was able to profit greatly from Andersen Mining Incorporated. In further testing the soil for coal deposits, Rorik had also discovered iron. He was able to expand his business even further, opening more mines and plants. Eventually, his humble property became an entire town. With Rorik's eventual licensing of the Bessemer process, this small town became a sprawling city.",
	make_shared<HTMLNode>(body_2),
	{
	},
	{
	},
};
const HTMLNode p_12 = {
	"p",
	"After so many years of hardship and struggle, Rorik finally saw prosperity, and lived the American dream. And his legacy continues with us to this day. Just ask his descendants! They're still alive and living in Rorik's End to this day. ",
	make_shared<HTMLNode>(body_2),
	{
	},
	{
	},
};
const HTMLNode p_13 = {
	"p",
	"Years later, Standard Combustion, seeing the amount of ready steel output to be used, opened some of the first automobile plants in Rorik's End. And we prosper to this day because of Rorik's tenacity.",
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
	},
	{
		{"title", "Rorik's End"},
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
HistoryRoriksendHTMLPage::HistoryRoriksendHTMLPage(int x, int y, int w, int h) : HTMLPage(make_shared<HTMLNode>(page), x, y, w, h) {

}