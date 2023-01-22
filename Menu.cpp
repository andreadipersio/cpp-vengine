#include "Menu.h"

Menu::Menu() {
	BOOST_LOG_TRIVIAL(debug) << "Menu Constructor";
}

MenuEntry& Menu::nextEntry() {
	if (index < entries.size() - 1) {
		index++;
	}

	return currentEntry();
}

MenuEntry& Menu::previousEntry() {
	if (index != 0) {
		index--;
	}

	return currentEntry();
}

MenuEntry& Menu::currentEntry() {
	return entries[index];
}

std::ostream& operator<<(std::ostream& os, MenuEntry& menuEntry) {
	if (menuEntry.is_selected)
		return os << "Menu Entry: " << menuEntry.id << " [SELECTED]";
	else
		return os << "Menu Entry: " << menuEntry.id;
}

void Menu::select() {
	for (auto i = 0; i < entries.size(); i++) {
		if (auto& entry = entries[i]; i == index)
			entry.is_selected = true;
		else
			entry.is_selected = false;
	}
}

