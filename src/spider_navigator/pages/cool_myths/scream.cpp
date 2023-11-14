#include "scream.h"
namespace CoolMythsScreamHTMLWindowNamespace {
std::shared_ptr<Text> text_4 = std::make_shared<Text>(
	4,
	"HOME",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "4"},
		{"href", "cool_myths/index"},
	}
);
std::shared_ptr<A> a_4 = std::make_shared<A>(
	4,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_4,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "4"},
		{"href", "cool_myths/index"},
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	3,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_4,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "8"},
	}
);
std::shared_ptr<Text> text_6 = std::make_shared<Text>(
	6,
	"Scream all you want. No one will hear you.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "1"},
	}
);
std::shared_ptr<P> p_6 = std::make_shared<P>(
	6,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_6,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "1"},
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	2,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_6,
		p_3,
	},
	std::unordered_map<std::string, std::string>{
		{"title", "The Scream"},
		{"background-color", "14"},
		{"color", "8"},
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
CoolMythsScreamHTMLWindow::CoolMythsScreamHTMLWindow(int x, int y, int w, int h) : HTMLWindow(CoolMythsScreamHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"cool_myths/index", CoolMythsIndexHTMLWindow::createWindow});


end();
}
