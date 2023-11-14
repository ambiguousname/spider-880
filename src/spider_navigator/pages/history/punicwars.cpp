#include "punicwars.h"
namespace HistoryPunicwarsHTMLWindowNamespace {
std::shared_ptr<Text> text_5 = std::make_shared<Text>(
	5,
	"Index",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "history/index"},
		{"color", "4"},
	}
);
std::shared_ptr<A> a_5 = std::make_shared<A>(
	5,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_5,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "history/index"},
		{"color", "4"},
	}
);
std::shared_ptr<P> p_4 = std::make_shared<P>(
	4,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_5,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_7 = std::make_shared<Text>(
	7,
	"Note: This article will be updated with more detail as my research continues. The hope is to eventually publish a book with extraordinary detail.",
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
	"THE PUNIC WARS are a fascinating section of history, for the genius of the western men involved and the scale of the giants that came into focus.",
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
	"On the one hand, was Carthage. A vicious giant, a master of unspeakable cruelty. Carthaginians owned slaves, suppressed revolts, and were determined to spread as far as they could.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_11 = std::make_shared<P>(
	11,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_11,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_13 = std::make_shared<Text>(
	13,
	"On the other, the Roman Republic. A true and pure democracy, Rome at this point had only involved itself in defensive conflicts to prevent aggression, and here was no different. Carthage would have to be taught a lesson.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_13 = std::make_shared<P>(
	13,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_13,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_15 = std::make_shared<Text>(
	15,
	"Carthaginians had the upper hand. Their fleets were massive, and well experienced. They controlled a much larger section of the Mediterranean than Rome.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_15 = std::make_shared<P>(
	15,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_15,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_17 = std::make_shared<Text>(
	17,
	"And so begins the great conflict of our the ancient age. Had these wars gone any differently, you or I might not exist at all. ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_17 = std::make_shared<P>(
	17,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_17,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_19 = std::make_shared<Text>(
	19,
	"More coming soon!",
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
std::shared_ptr<P> p_3 = std::make_shared<P>(
	3,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_19,
		p_17,
		p_15,
		p_13,
		p_11,
		p_9,
		p_7,
		p_4,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	2,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
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
		{"title", "The Punic Wars"},
	}
);
}
HistoryPunicwarsHTMLWindow::HistoryPunicwarsHTMLWindow(int x, int y, int w, int h) : HTMLWindow(HistoryPunicwarsHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"history/index", HistoryIndexHTMLWindow::createWindow});


end();
}
