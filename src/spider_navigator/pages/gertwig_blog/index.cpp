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
	"I've been playing with this stuff for a long while now (just turned 60. Boy am I old. I am eternally grateful to my wife for putting up with me :). I started on punchcards, I'm now on database management for the Bureau of Sabotage. I'm running this server on my home BSD distribution right now.",
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
	"My apologies to everyone currently using NavSab. You can see NavSab's development here: ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_11 = std::make_shared<Text>(
	"NavSab Development",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "gertwig_blog/navsab"},
		{"color", "4"},
	}
);
std::shared_ptr<A> a_11 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_11,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "gertwig_blog/navsab"},
		{"color", "4"},
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
std::shared_ptr<Text> text_13 = std::make_shared<Text>(
	"I'm tired. I don't know if I can do this anymore. I'm leaving the links up here, but... yeah. I've got no money and no friends. If you find me impaled on some spike somewhere, don't be surprised by the result.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_13 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_13,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_13,
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


end();
}
