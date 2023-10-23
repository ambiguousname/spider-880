#include "index.h"
namespace FivecoolbeansIndexHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	"Co-Founder of ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_5 = std::make_shared<Text>(
	"Star Information Systems",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "star_information_systems/index"},
	}
);
std::shared_ptr<A> a_5 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_5,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "star_information_systems/index"},
	}
);
std::shared_ptr<Text> text_6 = std::make_shared<Text>(
	".",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_6,
		a_5,
		text_3,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_8 = std::make_shared<Text>(
	"TODO",
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
std::shared_ptr<HTMLNode> body_2 = std::make_shared<HTMLNode>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_8,
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
		{"title", "5Coolbeans"},
	}
);
}
FivecoolbeansIndexHTMLWindow::FivecoolbeansIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(FivecoolbeansIndexHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"star_information_systems/index", StarInformationSystemsIndexHTMLWindow::createWindow});

}
