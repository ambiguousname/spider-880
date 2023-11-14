#include "index.h"
namespace HistoryIndexHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	"We begin bombing in five minutes. An Intellectual in name and spirit.",
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
std::shared_ptr<Text> text_6 = std::make_shared<Text>(
	"Rorik's End",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "history/roriksend"},
	}
);
std::shared_ptr<A> a_6 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_6,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "history/roriksend"},
	}
);
std::shared_ptr<P> p_5 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_6,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_9 = std::make_shared<Text>(
	"The Punic Wars",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "history/punicwars"},
	}
);
std::shared_ptr<A> a_9 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_9,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "history/punicwars"},
	}
);
std::shared_ptr<P> p_8 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_9,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Body> body_2 = std::make_shared<Body>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_8,
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
		{"title", "Outis"},
	}
);
}
HistoryIndexHTMLWindow::HistoryIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(HistoryIndexHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"history/roriksend", HistoryRoriksendHTMLWindow::createWindow});
	linked_windows.insert({"history/punicwars", HistoryPunicwarsHTMLWindow::createWindow});


end();
}
