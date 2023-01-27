#pragma once

#include <string>
#include <variant>
#include <vector>

using std::string;
using std::variant;
using std::vector;

class Menu_widget_choice {
public:
	Menu_widget_choice(vector<string> choices);

	string current_choice();
	void next_choice();
	void prev_choice();

private:
	vector<string> choices_;
	uint16_t index_ = 0;
};

using Menu_widget = variant<Menu_widget_choice*>;
