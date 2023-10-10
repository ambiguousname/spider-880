#include "feebdaed.h"
namespace DeadbeefFeebdaedHTMLWindowNamespace {
std::shared_ptr<Text> text_3 = std::make_shared<Text>(
	"I went spelunking with my friend Luke the other day.",
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
	"We've gone a few times. I don't live close to Egg Park, so it takes about an hour to make the drive up.",
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
std::shared_ptr<Text> text_7 = std::make_shared<Text>(
	"\"Careful!\" Luke shouts. I've slammed the door; he's particularly sensitive about the new coat of paint.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_7 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_7,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_9 = std::make_shared<Text>(
	"\"Sorry.\" I turn to the entrance. It's Egg Cave. The place reeks of sulfur, but it's by far the safest place to spelunk. Wide open spaces, a central cavern that connects all paths, and very few dead ends. ",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_9 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_9,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_11 = std::make_shared<Text>(
	"I do a quick check to make sure all our gear's there. Lights? Helmets? All the basic stuff is there. My plan is not to blow anyone's mind with our thoroughness. We're just here to have fun. \"We're good.\"",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_11 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_11,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_13 = std::make_shared<Text>(
	"We make our way into the tunnel that connects to the central cavern. It's a short walk through a somewhat cramped tunnel, but it opens up quickly. The view from the central cavern is always amazing.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_13 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_13,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_15 = std::make_shared<Text>(
	"As caverns go, it's stunning. The ceiling is so high, you can't even touch it with your fingers. The surface is smooth, flat, and dry. I am told that it was a lot more damp and dangerous, but Andersen Mining was interested in using this space as an investor showroom. That's the story, anyways. It didn't really pan out, since the rest of the caves were abandoned for who knows what reason.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_15 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_15,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_17 = std::make_shared<Text>(
	"I was Jessica Reyes.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<P> p_17 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_17,
	},
	std::unordered_map<std::string, std::string>{
	}
);
std::shared_ptr<Text> text_19 = std::make_shared<Text>(
	"I have been murdered.",
	std::vector<std::shared_ptr<HTMLNode>>{
	},
	std::unordered_map<std::string, std::string>{
		{"color", "1"},
	}
);
std::shared_ptr<P> p_19 = std::make_shared<P>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		text_19,
	},
	std::unordered_map<std::string, std::string>{
		{"color", "1"},
	}
);
std::shared_ptr<HTMLNode> body_2 = std::make_shared<HTMLNode>(
	"",
	std::vector<std::shared_ptr<HTMLNode>>{
		p_19,
		p_17,
		p_15,
		p_13,
		p_11,
		p_9,
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
		{"title", "FEEBDAED"},
	}
);
}
DeadbeefFeebdaedHTMLWindow::DeadbeefFeebdaedHTMLWindow(int x, int y, int w, int h) : HTMLWindow(DeadbeefFeebdaedHTMLWindowNamespace::html_1, x, y, w, h) {

}
