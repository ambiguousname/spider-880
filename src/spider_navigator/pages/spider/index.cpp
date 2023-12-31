#include "index.h"
namespace SpiderIndexHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	3,
	"Home | ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_5 = std::make_shared<Text>(
	5,
	"Policies",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "4"},
		{"href", "spider/policies"},
	}
);
std::shared_ptr<A> a_5 = std::make_shared<A>(
	5,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_5,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "4"},
		{"href", "spider/policies"},
	}
);
std::shared_ptr<Text> text_6 = std::make_shared<Text>(
	6,
	" | ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_8 = std::make_shared<Text>(
	8,
	"About Us",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "4"},
		{"href", "spider/about_us"},
	}
);
std::shared_ptr<A> a_8 = std::make_shared<A>(
	8,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_8,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "4"},
		{"href", "spider/about_us"},
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	3,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_8,
		text_6,
		a_5,
		text_3,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Img> img_10 = std::make_shared<Img>(
	10,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
		{"src", "./assets/spider.png"},
	}
);
std::shared_ptr<Text> text_11 = std::make_shared<Text>(
	11,
	"We're Spider Computing. We deliver authentic experiences, right at your desktop. Surf the web, write important documents, tabulate spreadsheets, all in the comfort of your own home. ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_11 = std::make_shared<P>(
	11,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_11,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_13 = std::make_shared<Text>(
	13,
	"Connect to our ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_15 = std::make_shared<Text>(
	15,
	"BBS",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "4"},
		{"href", "spider/bbs/index"},
	}
);
std::shared_ptr<A> a_15 = std::make_shared<A>(
	15,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_15,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "4"},
		{"href", "spider/bbs/index"},
	}
);
std::shared_ptr<Text> text_16 = std::make_shared<Text>(
	16,
	" to connect with our active community.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_13 = std::make_shared<P>(
	13,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_16,
		a_15,
		text_13,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_18 = std::make_shared<Text>(
	18,
	"Order your Spider-900 today: 1-800-555-6412.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_18 = std::make_shared<P>(
	18,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_18,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_20 = std::make_shared<Text>(
	20,
	"The only computing brand of Rorik's End's Bureau of Sabotage.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_20 = std::make_shared<P>(
	20,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_20,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	2,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_20,
		p_18,
		p_13,
		p_11,
		img_10,
		p_3,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<HTMLNode> html_1 = std::make_shared<HTMLNode>(
	1,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		body_2,
	},
	std::unordered_map<std::string, std::string>{
		{"title", "Spider Computing"},
	}
);
}
SpiderIndexHTMLWindow::SpiderIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(SpiderIndexHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"spider/policies", SpiderPoliciesHTMLWindow::createWindow});
	linked_windows.insert({"spider/about_us", SpiderAboutUsHTMLWindow::createWindow});
	linked_windows.insert({"spider/bbs/index", SpiderBbsIndexHTMLWindow::createWindow});


end();
}
