#include "policies.h"
namespace SpiderPoliciesHTMLWindowNamespace {
std::shared_ptr<Text> text_4 = std::make_shared<Text>(
	"Home",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "4"},
		{"href", "spider/index"},
	}
);
std::shared_ptr<A> a_4 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_4,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "4"},
		{"href", "spider/index"},
	}
);
std::shared_ptr<Text> text_5 = std::make_shared<Text>(
	" | Policies | ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_7 = std::make_shared<Text>(
	"About Us",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "4"},
		{"href", "spider/about_us"},
	}
);
std::shared_ptr<A> a_7 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_7,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "4"},
		{"href", "spider/about_us"},
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_7,
		text_5,
		a_4,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_9 = std::make_shared<Text>(
	"The following are all network and computing policies that can be enabled on Spider-brand computers: ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_9 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_9,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_11 = std::make_shared<Text>(
	"000 - Allow all content. Disabled by default.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_11 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_11,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_13 = std::make_shared<Text>(
	"100 - Censoring of Nudity or Sexual Content. Enabled by default.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_13 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_13,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_15 = std::make_shared<Text>(
	"150 - Censoring of Gore. Enabled by default.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_15 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_15,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_17 = std::make_shared<Text>(
	"200 - Censoring of Foul Language. Enabled by default for organizations of 50+ employees.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_17 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_17,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_19 = std::make_shared<Text>(
	"300 - Censoring of Games. Enabled by default for Spider-OS' Family mode, or any organizations.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_19 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_19,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_21 = std::make_shared<Text>(
	"400 - Censoring of Religious Iconography. Disabled by default.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_21 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_21,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_23 = std::make_shared<Text>(
	"500 - Censoring of Spider Computing and Standard Combustion proprietary secrets. Always enabled. ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_23 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_23,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_25 = std::make_shared<Text>(
	"All censoring policies are manually controlled by our staff of in-house content editors. Spider-brand computers are always prepared and able to deliver a safe computing experience for the consumer.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_25 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_25,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_27 = std::make_shared<Text>(
	"Purchase your Spider 900-Lite today for the safest the Internet has to offer.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<P> p_27 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_27,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_27,
		p_25,
		p_23,
		p_21,
		p_19,
		p_17,
		p_15,
		p_13,
		p_11,
		p_9,
		p_3,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "2"},
	}
);
std::shared_ptr<HTMLNode> html_1 = std::make_shared<HTMLNode>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		body_2,
	},
	std::unordered_map<std::string, std::string>{
		{"title", "Spider Policies"},
	}
);
}
SpiderPoliciesHTMLWindow::SpiderPoliciesHTMLWindow(int x, int y, int w, int h) : HTMLWindow(SpiderPoliciesHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"spider/index", SpiderIndexHTMLWindow::createWindow});
	linked_windows.insert({"spider/about_us", SpiderAboutUsHTMLWindow::createWindow});


end();
}
