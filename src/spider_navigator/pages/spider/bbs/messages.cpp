#include "messages.h"
namespace SpiderBbsMessagesHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	"TODO",
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
	"Powered by ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_7 = std::make_shared<Text>(
	"Mirror",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "mirror/index"},
	}
);
std::shared_ptr<A> a_7 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_7,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "mirror/index"},
	}
);
std::shared_ptr<Text> text_8 = std::make_shared<Text>(
	".",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_5 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_8,
		a_7,
		text_5,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<HTMLNode> body_2 = std::make_shared<HTMLNode>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
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
SpiderBbsMessagesHTMLWindow::SpiderBbsMessagesHTMLWindow(int x, int y, int w, int h) : HTMLWindow(SpiderBbsMessagesHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"mirror/index", MirrorIndexHTMLWindow::createWindow});

}
