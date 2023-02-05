#pragma once

#include <string>
#include <variant>
#include <vector>

#include <fmt/core.h>

#include "../events.h"
#include "../game_settings.h"

using std::string;
using std::variant;
using std::vector;

namespace menu {

namespace choices {

class Base_choice {
public:
	virtual Menu_event apply() = 0;
	virtual string label() = 0;
};


class Resolution_choice : public Base_choice {
public:
	Resolution_choice(uint16_t width, uint16_t heigth);
	Menu_event apply();
	string label();

private:
	uint16_t width_;
	uint16_t height_;
};

class Language_choice : public Base_choice {
public:
	Language_choice(Language_id);
	Menu_event apply();
	string label();

private:
	Language_id language_id_;
};

}

class Choice_widget {
public:
	Choice_widget(vector<choices::Base_choice*> choices);

	choices::Base_choice* current_choice();
	bool is_first();
	bool is_last();
	void next_choice();
	void prev_choice();

private:
	vector<choices::Base_choice*> choices_;
	uint16_t index_ = 0;
};

using Menu_widget = variant<Choice_widget*>;

}
