#include "index.h"
namespace SpiderBbsIndexHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	"Welcome to the Spider Computing BBS.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_3,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_6 = std::make_shared<Text>(
	"Announcements",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/bbs/announcements"},
	}
);
std::shared_ptr<A> a_6 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_6,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/bbs/announcements"},
	}
);
std::shared_ptr<P> p_5 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_6,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_9 = std::make_shared<Text>(
	"All User Messages",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/bbs/messages"},
	}
);
std::shared_ptr<A> a_9 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_9,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/bbs/messages"},
	}
);
std::shared_ptr<P> p_8 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_9,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_11 = std::make_shared<Text>(
	"Powered by ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_13 = std::make_shared<Text>(
	"Mirror",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "mirror/index"},
	}
);
std::shared_ptr<A> a_13 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_13,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "mirror/index"},
	}
);
std::shared_ptr<Text> text_14 = std::make_shared<Text>(
	".",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_11 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_14,
		a_13,
		text_11,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<HTMLNode> body_2 = std::make_shared<HTMLNode>(
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

}
