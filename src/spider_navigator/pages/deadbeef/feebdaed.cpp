#include "feebdaed.h"
namespace DeadbeefFeebdaedHTMLWindowNamespace {
std::shared_ptr<P> p_3 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_4 = std::make_shared<Text>(
	"I was Jessica Reyes.",
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
	"I have been murdered.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"color", "1"},
	}
);
std::shared_ptr<P> p_6 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_6,
	},
	std::unordered_map<std::string, std::string>{
		{"color", "1"},
	}
);
std::shared_ptr<HTMLNode> body_2 = std::make_shared<HTMLNode>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_6,
		p_4,
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
		{"title", "FEEBDAED"},
	}
);
}
DeadbeefFeebdaedHTMLWindow::DeadbeefFeebdaedHTMLWindow(int x, int y, int w, int h) : HTMLWindow(DeadbeefFeebdaedHTMLWindowNamespace::html_1, x, y, w, h) {

}
