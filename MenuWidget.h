#pragma once

#include <string>
#include <variant>
#include <vector>

using std::string;
using std::variant;
using std::vector;

class Menu_widget_choice {
public:
	vector<string> choices_ = { "640x480", "800x600", "1024x768" };
	uint16_t index_ = 0;
};

using Menu_widget = variant<Menu_widget_choice>;
