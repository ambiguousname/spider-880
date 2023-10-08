#include "navsab.h"
namespace GertwigBlogNavsabHTMLWindowNamespace {
std::shared_ptr<Text> text_4 = std::make_shared<Text>(
	"Home",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "gertwig_blog/index"},
	}
);
std::shared_ptr<A> a_4 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_4,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "gertwig_blog/index"},
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_4,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_6 = std::make_shared<Text>(
	"The current dedicated tracker for NavSab. Plans are in development for making it open source. The major issue is making the BuSab internal compiler accessible. The code is incompatible with every other compiler out there. BuSab computers screen machine code to verify where it was compiled from. It's a pain, but if any other BuSab members want to reach out, let me know. I could really use the help.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_6 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_6,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_8 = std::make_shared<Text>(
	"Networking is in at the very least, so you can view webpages.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_8 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_8,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_10 = std::make_shared<Text>(
	"Urgent Bugs:",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_10 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_10,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_12 = std::make_shared<Text>(
	"Multiple rendering issues - Image coloring and text positioning don't work on the first pass.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_12 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_12,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_14 = std::make_shared<Text>(
	"Major memory leakage for Spider-760s.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_14 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_14,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_16 = std::make_shared<Text>(
	"Typing \"DEADBEEF\" into NavSab window causes a crash.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_16 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_16,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_18 = std::make_shared<Text>(
	"Would be nice to have:",
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
	"Proper text wrapping.",
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
std::shared_ptr<Text> text_22 = std::make_shared<Text>(
	"Not all HTML tags are supported (lists, scripts, etc.).",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_22 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_22,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<HTMLNode> body_2 = std::make_shared<HTMLNode>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_22,
		p_20,
		p_18,
		p_16,
		p_14,
		p_12,
		p_10,
		p_8,
		p_6,
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
		{"title", "Brian Gertwig - NavSab Tracker"},
	}
);
}
GertwigBlogNavsabHTMLWindow::GertwigBlogNavsabHTMLWindow(int x, int y, int w, int h) : HTMLWindow(GertwigBlogNavsabHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"gertwig_blog/index", GertwigBlogIndexHTMLWindow::createWindow});

}
