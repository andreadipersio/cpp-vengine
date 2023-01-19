#include "Menu.h"

Menu::Menu() {
	BOOST_LOG_TRIVIAL(debug) << "Menu Constructor";
}

string Menu::nextEntry() {
	if (index < entries.size() - 1) {
		index++;
	}

	return currentEntry();
}

string Menu::previousEntry() {
	if (index != 0) {
		index--;
	}

	return currentEntry();
}

string Menu::currentEntry() {
	return entries[index];
}

