#include "menu_widget.h"

namespace menu {

namespace choices {

Resolution_choice::Resolution_choice(uint16_t width, uint16_t height)
	: width_(width), height_(height) {}

Menu_event Resolution_choice::apply() {
	return Menu_event(Menu_event_change_resolution(width_, height_));
}

string Resolution_choice::label() {
	return fmt::format("{}x{}", width_, height_);
}

Language_choice::Language_choice(Language_id language_id)
	: language_id_(language_id) {}

Menu_event Language_choice::apply() {
	return Menu_event(Menu_event_change_language(language_id_));
}

string Language_choice::label() {
	switch (language_id_) {
	case Language_id::DEUTSCH:
		return "Deutsch";
	case Language_id::ENGLISH:
		return "English";
	case Language_id::ITALIANO:
		return "Italiano";
	}
}

}

Choice_widget::Choice_widget(vector<choices::Base_choice*> choices) : choices_(choices) {};

bool Choice_widget::is_first() {
	return index_ == 0;
}

bool Choice_widget::is_last() {
	return index_ == choices_.size() - 1;
}

choices::Base_choice* Choice_widget::current_choice() {
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
