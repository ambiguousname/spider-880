#include "index.h"
namespace FivecoolbeansIndexHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	3,
	"Co-Founder of ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "5"},
	}
);
std::shared_ptr<Text> text_5 = std::make_shared<Text>(
	5,
	"Star Information Systems",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "4"},
		{"href", "star_information_systems/index"},
	}
);
std::shared_ptr<A> a_5 = std::make_shared<A>(
	5,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_5,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "4"},
		{"href", "star_information_systems/index"},
	}
);
std::shared_ptr<Text> text_6 = std::make_shared<Text>(
	6,
	".",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "5"},
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	3,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_6,
		a_5,
		text_3,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "5"},
	}
);
std::shared_ptr<Text> text_8 = std::make_shared<Text>(
	8,
	"Working on some cool ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "5"},
	}
);
std::shared_ptr<Text> text_10 = std::make_shared<Text>(
	10,
	"SPNPOLICY200",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "4"},
		{"href", "spider/policies"},
	}
);
std::shared_ptr<A> a_10 = std::make_shared<A>(
	10,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_10,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "4"},
		{"href", "spider/policies"},
	}
);
std::shared_ptr<Text> text_11 = std::make_shared<Text>(
	11,
	" for SIS.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "5"},
	}
);
std::shared_ptr<P> p_8 = std::make_shared<P>(
	8,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_11,
		a_10,
		text_8,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "5"},
	}
);
std::shared_ptr<Text> text_13 = std::make_shared<Text>(
	13,
	"Like the kind of stuff that will blow your mind out your body and into your soul. Whatever that means. My parents were hippies, don't sue me.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "5"},
	}
);
std::shared_ptr<P> p_13 = std::make_shared<P>(
	13,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_13,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "5"},
	}
);
std::shared_ptr<Text> text_15 = std::make_shared<Text>(
	15,
	"We started out on designing experimental chipsets for better processor speed, but we quickly pivoted into our new storage system: Ouranos. I can't share all the details yet, but you'll hear about it! ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "5"},
	}
);
std::shared_ptr<P> p_15 = std::make_shared<P>(
	15,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_15,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "5"},
	}
);
std::shared_ptr<Text> text_17 = std::make_shared<Text>(
	17,
	"If you're looking for a job at SIS by the way, we're probably hiring! As long as you live in the Rorik's End area. I know for me my commute is especially easy, since I live in the same District.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "5"},
	}
);
std::shared_ptr<P> p_17 = std::make_shared<P>(
	17,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_17,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "5"},
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	2,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_17,
		p_15,
		p_13,
		p_8,
		p_3,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "12"},
		{"color", "5"},
	}
);
std::shared_ptr<HTMLNode> html_1 = std::make_shared<HTMLNode>(
	1,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		body_2,
	},
	std::unordered_map<std::string, std::string>{
		{"title", "5Coolbeans"},
	}
);
}
FivecoolbeansIndexHTMLWindow::FivecoolbeansIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(FivecoolbeansIndexHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"star_information_systems/index", StarInformationSystemsIndexHTMLWindow::createWindow});
	linked_windows.insert({"spider/policies", SpiderPoliciesHTMLWindow::createWindow});


end();
}
