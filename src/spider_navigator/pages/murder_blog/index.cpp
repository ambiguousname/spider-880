#include "index.h"
namespace MurderBlogIndexHTMLWindowNamespace {
std::shared_ptr<HTMLNode> body_2 = std::make_shared<HTMLNode>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
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
		{"title", ""},
	}
);
}
MurderBlogIndexHTMLWindow::MurderBlogIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(MurderBlogIndexHTMLWindowNamespace::html_1, x, y, w, h) {

}
