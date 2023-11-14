#include "system.h"
namespace StarInformationSystemsSystemHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	"Congratulations to our BuSab patriots!",
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
	"The current NavSab version has a memory bug where it doesn't know how to precisely handle input, meaning that for some select phrases, it overflows into the page rendering and makes a new window.",
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
	"Usually it's complete gibberish, but I found a way to rig the network info for Star Information Systems' site to show this content. Minus potential memory leakage, I'm having fun!",
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
	"It's cool stuff!",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"color", "4"},
	}
);
std::shared_ptr<P> p_9 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_9,
	},
	std::unordered_map<std::string, std::string>{
		{"color", "4"},
	}
);
std::shared_ptr<Text> text_11 = std::make_shared<Text>(
	"I actually used to work for BuSab back when it was the posterboy for \"Safe Computing for Everyone\" (this was right after Wargames released). So I feel some kinship with you all. Shame it's all gone to crap.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_11 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_11,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_13 = std::make_shared<Text>(
	"You used to be able to dial into any number for any amount of time, no charge. For the purposes of security. In Rorik's End's Bureau of Sabotage. To be young and made of money; the Standard Combustion backing had its enormous uses. And I'm doing pretty well for myself after I left.",
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
std::shared_ptr<Text> text_15 = std::make_shared<Text>(
	"I left for a variety of reasons, and the harassment certainly didn't help. My mentor, Brian Gertwig (who I know is struggling with this NavSab bug, thank you!), made it all better though. I got a pretty sick pick for rock climbing. I'll have to digitize it sometime. ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_15 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_15,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_17 = std::make_shared<Text>(
	"Brian engraved a ram or some such on the hilt. For headbutting the competition away. Thanks Brian! I appreciate you so much.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_17 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_17,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_19 = std::make_shared<Text>(
	"And for everyone else: if you're struggling to figure out what to do, you could always apply for a career with SIS. We're growing fast.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_19 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_19,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_19,
		p_17,
		p_15,
		p_13,
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
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		body_2,
	},
	std::unordered_map<std::string, std::string>{
	}
);
}
StarInformationSystemsSystemHTMLWindow::StarInformationSystemsSystemHTMLWindow(int x, int y, int w, int h) : HTMLWindow(StarInformationSystemsSystemHTMLWindowNamespace::html_1, x, y, w, h) {


end();
}
