#pragma once

#include <string>
#include <variant>
#include <vector>

using std::string;
using std::variant;
using std::vector;

namespace menu {

class Choice_widget {
public:
	Choice_widget(vector<string> choices);

	string current_choice();
	bool is_first();
	bool is_last();
	void next_choice();
	void prev_choice();

private:
	vector<string> choices_;
	uint16_t index_ = 0;
};

using Menu_widget = variant<Choice_widget*>;

}
