#include "menu_widget.h"

Menu_widget_choice::Menu_widget_choice(vector<string> choices) : choices_(choices) {};

bool Menu_widget_choice::is_first() {
	return index_ == 0;
}

bool Menu_widget_choice::is_last() {
	return index_ == choices_.size() - 1;
}

string Menu_widget_choice::current_choice() {
	return choices_[index_];
}

void Menu_widget_choice::next_choice() {
	if (is_last()) {
		index_ = 0;
	} else { 
		index_++;
	}
}

void Menu_widget_choice::prev_choice() {
	if (is_first()) {
		index_ = choices_.size() - 1;
	} else { 
		index_--;
	}
}
