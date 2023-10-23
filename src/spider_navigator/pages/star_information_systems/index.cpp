#include "index.h"
namespace StarInformationSystemsIndexHTMLWindowNamespace {
std::shared_ptr<Img> img_3 = std::make_shared<Img>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"src", "./assets/sis_logo.png"},
	}
);
std::shared_ptr<Text> text_4 = std::make_shared<Text>(
	"Star Information Systems - Cutting-edge hardware for today's information age.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_4 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_4,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_6 = std::make_shared<Text>(
	"Our revolutionary Ouranos system has 1000% more capacity than any compact disc, reads faster, and is compatible with any existing computational system.",
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
	"Call today for a demonstration: 555-135-7918.",
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
	"Or stop by our offices:",
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
	"242 Sycamore Lane",
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
	"Rorik's End, Zipcode 532",
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
	"Founded by ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_18 = std::make_shared<Text>(
	"Jessica Reyes",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "fivecoolbeans/index"},
	}
);
std::shared_ptr<A> a_18 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_18,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "fivecoolbeans/index"},
	}
);
std::shared_ptr<Text> text_19 = std::make_shared<Text>(
	" and ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_21 = std::make_shared<Text>(
	"Luke Schiff",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "lschiff/index"},
	}
);
std::shared_ptr<A> a_21 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_21,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "lschiff/index"},
	}
);
std::shared_ptr<Text> text_22 = std::make_shared<Text>(
	".",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_16 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_22,
		a_21,
		text_19,
		a_18,
		text_16,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<HTMLNode> body_2 = std::make_shared<HTMLNode>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_16,
		p_14,
		p_12,
		p_10,
		p_8,
		p_6,
		p_4,
		img_3,
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
		{"title", "Star Information Systems"},
	}
);
}
StarInformationSystemsIndexHTMLWindow::StarInformationSystemsIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(StarInformationSystemsIndexHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"fivecoolbeans/index", FivecoolbeansIndexHTMLWindow::createWindow});
	linked_windows.insert({"lschiff/index", LschiffIndexHTMLWindow::createWindow});

}
