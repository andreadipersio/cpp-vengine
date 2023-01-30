#include "menu_widget.h"

namespace menu {

Choice_widget::Choice_widget(vector<string> choices) : choices_(choices) {};

bool Choice_widget::is_first() {
	return index_ == 0;
}

bool Choice_widget::is_last() {
	return index_ == choices_.size() - 1;
}

string Choice_widget::current_choice() {
	return choices_[index_];
}

void Choice_widget::next_choice() {
	if (is_last()) {
		index_ = 0;
	} else {
		index_++;
	}
}

void Choice_widget::prev_choice() {
	if (is_first()) {
		index_ = choices_.size() - 1;
	} else {
		index_--;
	}
}

}
