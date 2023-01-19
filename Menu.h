#pragma once

#include <boost/log/trivial.hpp>
#include <boost/locale.hpp>
#include <vector>
#include <string>

using std::vector, std::string;
using boost::locale::translate;

class Menu {
public:
	unsigned int index = 0;
	const vector<string> entries = { translate("New Game")
			       										 , translate("Load Game")
						      							 , translate("Settings")
								      					 , translate("Quit") };

	string nextEntry();
	string previousEntry();
	string currentEntry();

	Menu();
};
