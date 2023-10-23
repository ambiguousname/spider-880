#include "index.h"
namespace LschiffIndexHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	"TODO:",
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
std::shared_ptr<HTMLNode> body_2 = std::make_shared<HTMLNode>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
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
		{"title", "Luke Schiff"},
	}
);
}
LschiffIndexHTMLWindow::LschiffIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(LschiffIndexHTMLWindowNamespace::html_1, x, y, w, h) {

}
