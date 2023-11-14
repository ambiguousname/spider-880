#include "lastresort.h"
namespace StarInformationSystemsLastresortHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	3,
	"CUT MY LIFE INTO PIECES",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "1"},
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	3,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_3,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "1"},
	}
);
std::shared_ptr<Text> text_5 = std::make_shared<Text>(
	5,
	"THIS IS MY LAST RESORT",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "1"},
	}
);
std::shared_ptr<P> p_5 = std::make_shared<P>(
	5,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_5,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "1"},
	}
);
std::shared_ptr<Text> text_7 = std::make_shared<Text>(
	7,
	"- Ebony Dark'ness Dementia Raven Way",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "1"},
	}
);
std::shared_ptr<P> p_7 = std::make_shared<P>(
	7,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_7,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "1"},
	}
);
std::shared_ptr<Text> text_9 = std::make_shared<Text>(
	9,
	"Enoby and Draco 4ever",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "1"},
	}
);
std::shared_ptr<P> p_9 = std::make_shared<P>(
	9,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_9,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "1"},
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	2,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_9,
		p_7,
		p_5,
		p_3,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "0"},
		{"color", "1"},
	}
);
std::shared_ptr<HTMLNode> html_1 = std::make_shared<HTMLNode>(
	1,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		body_2,
	},
	std::unordered_map<std::string, std::string>{
	}
);
}
StarInformationSystemsLastresortHTMLWindow::StarInformationSystemsLastresortHTMLWindow(int x, int y, int w, int h) : HTMLWindow(StarInformationSystemsLastresortHTMLWindowNamespace::html_1, x, y, w, h) {


end();
}
