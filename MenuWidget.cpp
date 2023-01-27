#include "MenuWidget.h"

Menu_widget_choice::Menu_widget_choice(vector<string> choices) : choices_(choices) {};

string Menu_widget_choice::current_choice() {
	return choices_[index_];
}

void Menu_widget_choice::next_choice() {
	if (index_ < choices_.size() - 1) {
		index_++;
	} else { 
		index_ = 0;
	}
}

void Menu_widget_choice::prev_choice() {
	if (index_ > 0) {
		index_--;
	} else { 
		index_ = choices_.size() - 1;
	}
}
