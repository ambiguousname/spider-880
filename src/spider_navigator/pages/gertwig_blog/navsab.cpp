#include "navsab.h"
namespace GertwigBlogNavsabHTMLWindowNamespace {
std::shared_ptr<Text> text_4 = std::make_shared<Text>(
	4,
	"Home",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
		{"href", "gertwig_blog/index"},
		{"color", "4"},
	}
);
std::shared_ptr<A> a_4 = std::make_shared<A>(
	4,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_4,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
		{"href", "gertwig_blog/index"},
		{"color", "4"},
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	3,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_4,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_6 = std::make_shared<Text>(
	6,
	"The current page for NavSab. Plans are in development for making it open source.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_6 = std::make_shared<P>(
	6,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_6,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_8 = std::make_shared<Text>(
	8,
	"The major issue is the BuSab Internal C Compiler. The binaries are only compatible with Spider-500+, and only on BuSab models. BuSab OS screens the machine code to verify that a compiled program has an encrypted checksum generated from the BICC. And there are some C features that are wholly unique to BICC.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_8 = std::make_shared<P>(
	8,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_8,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_10 = std::make_shared<Text>(
	10,
	"It's a pain, but if any other BuSab members want to reach out (especially with valid checksum generators, or any custom compiler kits), let me know. I could really use the help.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_10 = std::make_shared<P>(
	10,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_10,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_12 = std::make_shared<Text>(
	12,
	"Networking is in at the very least, so you can view webpages.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_12 = std::make_shared<P>(
	12,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_12,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_14 = std::make_shared<Text>(
	14,
	"Urgent Bugs:",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_14 = std::make_shared<P>(
	14,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_14,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_16 = std::make_shared<Text>(
	16,
	"Loading <a> tags from Mirror's output are not consistent with real links, reducing them to plaintext for now.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_16 = std::make_shared<P>(
	16,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_16,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_18 = std::make_shared<Text>(
	18,
	"Major memory leakage for Spider-760s.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_18 = std::make_shared<P>(
	18,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_18,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_20 = std::make_shared<Text>(
	20,
	"Typing \"DEADBEEF\" into a NavSab window causes a crash.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_20 = std::make_shared<P>(
	20,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_20,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_22 = std::make_shared<Text>(
	22,
	"Would be nice to have:",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_22 = std::make_shared<P>(
	22,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_22,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_24 = std::make_shared<Text>(
	24,
	"In-built padding that doesn't leave awkward whitespace from <style> tags.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_24 = std::make_shared<P>(
	24,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_24,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_26 = std::make_shared<Text>(
	26,
	"Maximize button that doesn't screw up sizing.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_26 = std::make_shared<P>(
	26,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_26,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_28 = std::make_shared<Text>(
	28,
	"Proper text wrapping.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_28 = std::make_shared<P>(
	28,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_28,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_30 = std::make_shared<Text>(
	30,
	"Following that, text you can actually select and copy. I know because I sometimes have trouble reading these webpages myself.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_30 = std::make_shared<P>(
	30,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_30,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_32 = std::make_shared<Text>(
	32,
	"Fully centered (and resizing) text.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_32 = std::make_shared<P>(
	32,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_32,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_34 = std::make_shared<Text>(
	34,
	"Not all HTML tags are supported (lists, plaintext, headers, etc.)",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_34 = std::make_shared<P>(
	34,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_34,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_36 = std::make_shared<Text>(
	36,
	"Things I can't fix:",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_36 = std::make_shared<P>(
	36,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_36,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_38 = std::make_shared<Text>(
	38,
	"Swearing is blocked as per ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Text> text_40 = std::make_shared<Text>(
	40,
	"SPNPOLICY200",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
		{"href", "spider/policies"},
		{"color", "4"},
	}
);
std::shared_ptr<A> a_40 = std::make_shared<A>(
	40,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_40,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
		{"href", "spider/policies"},
		{"color", "4"},
	}
);
std::shared_ptr<Text> text_41 = std::make_shared<Text>(
	41,
	".",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<P> p_38 = std::make_shared<P>(
	38,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_41,
		a_40,
		text_38,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "11"},
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	2,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_38,
		p_36,
		p_34,
		p_32,
		p_30,
		p_28,
		p_26,
		p_24,
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
		{"background-color", "11"},
	}
);
std::shared_ptr<HTMLNode> html_1 = std::make_shared<HTMLNode>(
	1,
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
	linked_windows.insert({"spider/policies", SpiderPoliciesHTMLWindow::createWindow});


end();
}
