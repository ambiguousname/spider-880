#include "bulletin.h"
namespace UbbsBulletinHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	"Missing Persons",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"color", "2"},
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_3,
	},
	std::unordered_map<std::string, std::string>{
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_5 = std::make_shared<Text>(
	"For anyone who knows any info about 5coolbeans (Jessica Reyes), lschiff (Luke Schiff), or brian. (Brian Gertwig), please contact us.All have been offline for about a week now, and friends/family have not been able to find them in the real world.",
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
	"Update  to Mirror",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"color", "2"},
	}
);
std::shared_ptr<P> p_7 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_7,
	},
	std::unordered_map<std::string, std::string>{
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_9 = std::make_shared<Text>(
	"Hey, Mirror's getting a new release soon, so within the next week we'll be able to restore the old message boards.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_9 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_9,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_11 = std::make_shared<Text>(
	"Temporary Board Merge",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"color", "2"},
	}
);
std::shared_ptr<P> p_11 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_11,
	},
	std::unordered_map<std::string, std::string>{
		{"color", "2"},
	}
);
std::shared_ptr<Text> text_13 = std::make_shared<Text>(
	"Hey all. We're working on restoring the old message board functionality, but we're currently trying to keep Mirror support for our HTML end. You'll have to post in the general board for now.",
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
	"Powered by ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_17 = std::make_shared<Text>(
	"Mirror",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "mirror/index"},
	}
);
std::shared_ptr<A> a_17 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_17,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "mirror/index"},
	}
);
std::shared_ptr<Text> text_18 = std::make_shared<Text>(
	".",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_15 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_18,
		a_17,
		text_15,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
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
		{"title", "UBBS"},
	}
);
}
UbbsBulletinHTMLWindow::UbbsBulletinHTMLWindow(int x, int y, int w, int h) : HTMLWindow(UbbsBulletinHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"mirror/index", MirrorIndexHTMLWindow::createWindow});


end();
}
