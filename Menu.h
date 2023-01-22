#pragma once

#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/locale.hpp>
#include <vector>
#include <string>

using std::vector, std::string;
using boost::locale::translate;

struct MenuEntry {
	string id;
	bool is_selected;
};

class Menu {
public:
	unsigned int index = 0;
	vector<MenuEntry> entries = {
		{"New Game", true},
		{"Load Game", false},
		{"Settings", false},
		{"Quit Game", false}
	};

	MenuEntry& nextEntry();
	MenuEntry& previousEntry();
	MenuEntry& currentEntry();
	void select();

	Menu();
};

std::ostream& operator<<(std::ostream& os, MenuEntry& menuEntry); 
