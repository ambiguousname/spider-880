#include "index.h"
namespace SpiderBbsIndexHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	3,
	"Welcome to the Spider Computing BBS.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	3,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_3,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_6 = std::make_shared<Text>(
	6,
	"Announcements",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/bbs/announcements"},
		{"color", "4"},
	}
);
std::shared_ptr<A> a_6 = std::make_shared<A>(
	6,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_6,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/bbs/announcements"},
		{"color", "4"},
	}
);
std::shared_ptr<P> p_5 = std::make_shared<P>(
	5,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_6,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_9 = std::make_shared<Text>(
	9,
	"All User Messages",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/bbs/messages"},
		{"color", "4"},
	}
);
std::shared_ptr<A> a_9 = std::make_shared<A>(
	9,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_9,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/bbs/messages"},
		{"color", "4"},
	}
);
std::shared_ptr<P> p_8 = std::make_shared<P>(
	8,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_9,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_11 = std::make_shared<Text>(
	11,
	"Powered by ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_13 = std::make_shared<Text>(
	13,
	"Mirror",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "mirror/index"},
		{"color", "4"},
	}
);
std::shared_ptr<A> a_13 = std::make_shared<A>(
	13,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_13,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "mirror/index"},
		{"color", "4"},
	}
);
std::shared_ptr<Text> text_14 = std::make_shared<Text>(
	14,
	".",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_11 = std::make_shared<P>(
	11,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_14,
		a_13,
		text_11,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	2,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_11,
		p_8,
		p_5,
		p_3,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<HTMLNode> html_1 = std::make_shared<HTMLNode>(
	1,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		body_2,
	},
	std::unordered_map<std::string, std::string>{
		{"title", "Spider Computing BBS"},
	}
);
}
SpiderBbsIndexHTMLWindow::SpiderBbsIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(SpiderBbsIndexHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"spider/bbs/announcements", SpiderBbsAnnouncementsHTMLWindow::createWindow});
	linked_windows.insert({"spider/bbs/messages", SpiderBbsMessagesHTMLWindow::createWindow});
	linked_windows.insert({"mirror/index", MirrorIndexHTMLWindow::createWindow});


end();
}
