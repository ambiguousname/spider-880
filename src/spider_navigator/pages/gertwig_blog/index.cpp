#include "index.h"
namespace GertwigBlogIndexHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	"Hi! I'm Brian.",
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
std::shared_ptr<Text> text_5 = std::make_shared<Text>(
	"I've been playing with this stuff for a long while now. I started on punchcards, I'm now on database management for the Bureau of Sabotage.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_5 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_5,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_7 = std::make_shared<Text>(
	"Currently developing the Bureau of Sabotage Network Navigator as a spare time project.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_7 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_7,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_9 = std::make_shared<Text>(
	"My apologies to everyone currently using NavSab. You can see the issues being tracked here: ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<A> a_11 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "gertwig_blog/navsab"},
	}
);
std::shared_ptr<P> p_9 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_11,
		text_9,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<HTMLNode> body_2 = std::make_shared<HTMLNode>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_9,
		p_7,
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
		{"title", "Brian Gertwig's Homepage"},
	}
);
}
GertwigBlogIndexHTMLWindow::GertwigBlogIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(GertwigBlogIndexHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"gertwig_blog/navsab", GertwigBlogNavsabHTMLWindow::createWindow});

}
