#include "index.h"
namespace MirrorIndexHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	3,
	"Greetings mortals, and welcome to... the MIRROR!",
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
std::shared_ptr<Text> text_5 = std::make_shared<Text>(
	5,
	"The MIRROR is a revolutionary on-line library and social playground.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_5 = std::make_shared<P>(
	5,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_5,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_7 = std::make_shared<Text>(
	7,
	"The MIRROR runs as a daemon process to convert your BBS system into web-friendly HTML, written wholly in C. ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_7 = std::make_shared<P>(
	7,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_7,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_9 = std::make_shared<Text>(
	9,
	"The MIRROR is the next step in connectivity, and is spreading like wildfire among Rorik's End tech community:",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_9 = std::make_shared<P>(
	9,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_9,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_11 = std::make_shared<Text>(
	11,
	"Used by ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_13 = std::make_shared<Text>(
	13,
	"Spider Computing BBS",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/bbs/index"},
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
		{"href", "spider/bbs/index"},
		{"color", "4"},
	}
);
std::shared_ptr<Text> text_14 = std::make_shared<Text>(
	14,
	" and ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_16 = std::make_shared<Text>(
	16,
	"UBBS",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "ubbs/index"},
		{"color", "4"},
	}
);
std::shared_ptr<A> a_16 = std::make_shared<A>(
	16,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_16,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "ubbs/index"},
		{"color", "4"},
	}
);
std::shared_ptr<Text> text_17 = std::make_shared<Text>(
	17,
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
		text_17,
		a_16,
		text_14,
		a_13,
		text_11,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_19 = std::make_shared<Text>(
	19,
	"Ready to get started? Check out our set-up guide (coming soon!)",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_19 = std::make_shared<P>(
	19,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_19,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	2,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_19,
		p_11,
		p_9,
		p_7,
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
		{"title", "The Mirror"},
	}
);
}
MirrorIndexHTMLWindow::MirrorIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(MirrorIndexHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"spider/bbs/index", SpiderBbsIndexHTMLWindow::createWindow});
	linked_windows.insert({"ubbs/index", UbbsIndexHTMLWindow::createWindow});


end();
}
