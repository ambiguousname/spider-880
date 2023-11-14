#include "about_us.h"
namespace SpiderAboutUsHTMLWindowNamespace {
std::shared_ptr<Text> text_4 = std::make_shared<Text>(
	"Home",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/index"},
	}
);
std::shared_ptr<A> a_4 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_4,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/index"},
	}
);
std::shared_ptr<Text> text_5 = std::make_shared<Text>(
	" | ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_7 = std::make_shared<Text>(
	"Policies",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/policies"},
	}
);
std::shared_ptr<A> a_7 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_7,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "spider/policies"},
	}
);
std::shared_ptr<Text> text_8 = std::make_shared<Text>(
	" | About Us",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_8,
		a_7,
		text_5,
		a_4,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_10 = std::make_shared<Text>(
	"Spider Computing was founded as the Spider Speculative Business Unit in 1968 by Standard Combustion to explore potential investment opportunities in an ever-shifting market. We found a home with the transistor. Since then, we've been aggressively taking the personal and business computing market by storm with our yearly releases of the Spider series.",
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
	"Order a Spider-900 today for your own home or business. Satisfaction guaranteed.",
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
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_12,
		p_10,
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
		{"title", "About Us"},
	}
);
}
SpiderAboutUsHTMLWindow::SpiderAboutUsHTMLWindow(int x, int y, int w, int h) : HTMLWindow(SpiderAboutUsHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"spider/index", SpiderIndexHTMLWindow::createWindow});
	linked_windows.insert({"spider/policies", SpiderPoliciesHTMLWindow::createWindow});


end();
}
