#include "index.h"
namespace UbbsIndexHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	"____ ___ __________ __________   _________ |    |   \\______   \\______   \ /   _____/ |    |   / |    |  _/ |    |  _/ \_____  \  |    |  /  |    |   \ |    |   \ /        \ |______/   |______  / |______  //_______  /   \/         \/         \/  Universal Bulletin Board Systemfor Rorik's End",
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
	"Welcome back, MIRRORAGENT",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_5 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_5,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_8 = std::make_shared<Text>(
	"System Bulletins",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "ubbs/bulletin"},
	}
);
std::shared_ptr<A> a_8 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_8,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "ubbs/bulletin"},
	}
);
std::shared_ptr<P> p_7 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_8,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_11 = std::make_shared<Text>(
	"User Bulletins",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "ubbs/ubulletin"},
	}
);
std::shared_ptr<A> a_11 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_11,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "ubbs/ubulletin"},
	}
);
std::shared_ptr<P> p_10 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		a_11,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_13 = std::make_shared<Text>(
	"Powered by ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_15 = std::make_shared<Text>(
	"Mirror",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"href", "mirror/index"},
	}
);
std::shared_ptr<A> a_15 = std::make_shared<A>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_15,
	},
	std::unordered_map<std::string, std::string>{
		{"href", "mirror/index"},
	}
);
std::shared_ptr<Text> text_16 = std::make_shared<Text>(
	".",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_13 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_16,
		a_15,
		text_13,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<HTMLNode> body_2 = std::make_shared<HTMLNode>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_13,
		p_10,
		p_7,
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
		{"title", "UBBS"},
	}
);
}
UbbsIndexHTMLWindow::UbbsIndexHTMLWindow(int x, int y, int w, int h) : HTMLWindow(UbbsIndexHTMLWindowNamespace::html_1, x, y, w, h) {
	linked_windows.insert({"ubbs/bulletin", UbbsBulletinHTMLWindow::createWindow});
	linked_windows.insert({"ubbs/ubulletin", UbbsUbulletinHTMLWindow::createWindow});
	linked_windows.insert({"mirror/index", MirrorIndexHTMLWindow::createWindow});

}
