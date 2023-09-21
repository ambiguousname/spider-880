#include "pages.h"
const Text text_3 = {
	"RORIK ANDERSEN was the only son of two loving parents. A descendant of Danish immigrants, his family came to the Americas in the 1690s as sugar plantation owners in the West Indies (now the Virgin Islands) and had held onto their land ever since. Rorik himself was born in 1826 to a thriving industry, with a booming economy and many happy workers.",
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
const Text text_5 = {
	"He took to his work diligently, improving the lives of himself, his family, and his workers. All was good for a time as he worked hard to provide for himself. Overseeing one of the nation's largest plantations was a lot of work.",
	{
	},
	{
	},
};
const P p_5 = {
	"",
	{
		make_shared<HTMLNode>(text_5),
	},
	{
	},
};
const Text text_7 = {
	"Things soured, as Rorik felt the cold grip of interference on his harvest. At the time he had taken up to writing Graham Waldorf, a fellow plantation owner in the Americas. In his correspondence, Rorik says: \"I am perplexed by the increasing demands of those defective in mind, body, and spirit to take up my burdens. None of the brigands insisting my dignity have struggled as I have in the higher duty to which I take.\" Rorik was upset by the devestation he saw in his country. He took with him his family and belongings on July 4th of 1848, and looked for greener pastures with his American comrades.",
	{
	},
	{
	},
};
const P p_7 = {
	"",
	{
		make_shared<HTMLNode>(text_7),
	},
	{
	},
};
const Text text_9 = {
	"It was a good thing too: Danish parliament sold the Virgin Islands to the U.S. 4 years later. But Rorik had lost much from the sudden move, and was eager to start again. He took a loan from his American friends, and set up another plantation in Louisiana. He worked doubly hard to ensure the prosperity of his lands.",
	{
	},
	{
	},
};
const P p_9 = {
	"",
	{
		make_shared<HTMLNode>(text_9),
	},
	{
	},
};
const Text text_11 = {
	"But not all was well. While most were welcoming of his new venture, there were some that would not accept him for his differences as a Danish immigrant. Rorik once wrote: \"My neighbors do not take kindly to my presence. I have managed to buy what land I could in further pursuit of my duty; they take this as an insult. I have resolved to not let their hearts temper my spirits. I sleep contented by the Kalthoff repeater resting by my bedside.\"",
	{
	},
	{
	},
};
const P p_11 = {
	"",
	{
		make_shared<HTMLNode>(text_11),
	},
	{
	},
};
const Text text_13 = {
	"Even with his determination tested, Rorik would see failure yet again: war came about 6 years into the founding of his new home. As Rorik puts it in another correspondence to Waldorf: \"The balance of my hearth is threatened by divisions on all sides. My crop is soured by foul weather and tempers alike.\"",
	{
	},
	{
	},
};
const P p_13 = {
	"",
	{
		make_shared<HTMLNode>(text_13),
	},
	{
	},
};
const Text text_15 = {
	"War came to the plantation, and Rorik found himself moving yet again. He was forced to move to desolate plains with hardly any of the wealth and status he had once held. Worse, he found the soil lacked any substantial nutrients that he could use to grow crops.",
	{
	},
	{
	},
};
const P p_15 = {
	"",
	{
		make_shared<HTMLNode>(text_15),
	},
	{
	},
};
const Text text_17 = {
	"But innovation would strike when he discovered coal while wandering the border of his new property. After boring into the earth to test the amount of suitable coal, Rorik found it to be plentiful. He got straight to work. ",
	{
	},
	{
	},
};
const P p_17 = {
	"",
	{
		make_shared<HTMLNode>(text_17),
	},
	{
	},
};
const Text text_19 = {
	"Within a few years, Rorik was able to use what meager resources he had left to hire laborers for a coal mine. From there, he was able to profit greatly from Andersen Mining Incorporated. In further testing the soil for coal deposits, Rorik had also discovered iron. He was able to expand his business even further, opening more mines and plants. Eventually, his humble property became an entire town. With Rorik's eventual licensing of the Bessemer process, this small town became a sprawling city.",
	{
	},
	{
	},
};
const P p_19 = {
	"",
	{
		make_shared<HTMLNode>(text_19),
	},
	{
	},
};
const Text text_21 = {
	"After so many years of hardship and struggle, Rorik finally saw prosperity, and lived the American dream. And his legacy continues with us to this day. Just ask his descendants! They're still alive and living in Rorik's End to this day. ",
	{
	},
	{
	},
};
const P p_21 = {
	"",
	{
		make_shared<HTMLNode>(text_21),
	},
	{
	},
};
const Text text_23 = {
	"Years later, Standard Combustion, seeing the amount of ready steel output to be used, opened some of the first automobile plants in Rorik's End. And we prosper to this day because of Rorik's tenacity.",
	{
	},
	{
	},
};
const P p_23 = {
	"",
	{
		make_shared<HTMLNode>(text_23),
	},
	{
	},
};
const HTMLNode body_2 = {
	"",
	{
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
		{"title", "Rorik's End"},
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
HistoryRoriksendHTMLWindow::HistoryRoriksendHTMLWindow(int x, int y, int w, int h) : HTMLWindow(make_shared<HTMLNode>(html_1), x, y, w, h) {

}
