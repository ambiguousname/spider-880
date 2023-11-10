#include "babababa.h"
namespace DeadbeefBabababaHTMLWindowNamespace {
std::shared_ptr<P> p_3 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
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
	}
);
}
DeadbeefBabababaHTMLWindow::DeadbeefBabababaHTMLWindow(int x, int y, int w, int h) : HTMLWindow(DeadbeefBabababaHTMLWindowNamespace::html_1, x, y, w, h) {


end();
}
