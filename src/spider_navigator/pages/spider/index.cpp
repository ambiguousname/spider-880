#include "index.h"
namespace SpiderIndexHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	"Home | ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_5 = std::make_shared<Text>(
	"Policies",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/policies"},
	}
);
std::shared_ptr<A> a_5 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_5,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/policies"},
	}
);
std::shared_ptr<Text> text_6 = std::make_shared<Text>(
	" | ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_8 = std::make_shared<Text>(
	"About Us",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/about_us"},
	}
);
std::shared_ptr<A> a_8 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_8,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/about_us"},
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_8,
		text_6,
		a_5,
		text_3,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Img> img_10 = std::make_shared<Img>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"src", "./assets/spider.png"},
	}
);
std::shared_ptr<Text> text_11 = std::make_shared<Text>(
	"We're Spider Computing. We deliver authentic experiences, right at your desktop. Surf the web, write important documents, tabulate spreadsheets, all in the comfort of your own home. ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_11 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_11,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_13 = std::make_shared<Text>(
	"Connect to our ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_15 = std::make_shared<Text>(
	"BBS",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/bbs/index"},
	}
);
std::shared_ptr<A> a_15 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_15,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/bbs/index"},
	}
);
std::shared_ptr<Text> text_16 = std::make_shared<Text>(
	" to connect with our active community.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_13 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_16,
		a_15,
		text_13,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_18 = std::make_shared<Text>(
	"Order your Spider-900 today: 555-416-6412.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_18 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_18,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_20 = std::make_shared<Text>(
	"The only computing brand of Rorik's End's Bureau of Sabotage.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_20 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_20,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<HTMLNode> body_2 = std::make_shared<HTMLNode>(
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
	}
);
std::shared_ptr<HTMLNode> html_1 = std::make_shared<HTMLNode>(
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

}
