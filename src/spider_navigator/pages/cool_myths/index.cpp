#include "index.h"
namespace CoolMythsIndexHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	3,
	"HOME",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "8"},
	}
);
std::shared_ptr<P> p_3 = std::make_shared<P>(
	3,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_3,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "8"},
	}
);
std::shared_ptr<Text> text_5 = std::make_shared<Text>(
	5,
	"Welcome to my home. I'm mostly figuring out how these servers work, but I've put up some cool stuff in the meantime.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "8"},
	}
);
std::shared_ptr<P> p_5 = std::make_shared<P>(
	5,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_5,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "8"},
	}
);
std::shared_ptr<Text> text_8 = std::make_shared<Text>(
	8,
	"Story 1",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "4"},
		{"href", "cool_myths/scream"},
	}
);
std::shared_ptr<A> a_8 = std::make_shared<A>(
	8,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_8,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "4"},
		{"href", "cool_myths/scream"},
	}
);
std::shared_ptr<P> p_7 = std::make_shared<P>(
	7,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_8,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "8"},
	}
);
std::shared_ptr<Text> text_11 = std::make_shared<Text>(
	11,
	"Story 2",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "4"},
		{"href", "cool_myths/theend"},
	}
);
std::shared_ptr<A> a_11 = std::make_shared<A>(
	11,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_11,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "4"},
		{"href", "cool_myths/theend"},
	}
);
std::shared_ptr<P> p_10 = std::make_shared<P>(
	10,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_11,
	},
	std::unordered_map<std::string, std::string>{
		{"background-color", "14"},
		{"color", "8"},
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	2,
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_10,
		p_7,
		p_5,
		p_3,
	},
	std::unordered_map<std::string, std::string>{
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
		{"title", "Cool Myths"},
	}
);
}
CoolMythsIndexHTMLWindow::CoolMythsIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(CoolMythsIndexHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"cool_myths/scream", CoolMythsScreamHTMLWindow::createWindow});
	linked_windows.insert({"cool_myths/theend", CoolMythsTheendHTMLWindow::createWindow});


end();
}
