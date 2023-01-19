#pragma once

#include <boost/locale.hpp>
#include <vector>
#include <string>

using std::vector, std::string;
using boost::locale::translate;

class Menu {
public:
	int index = 0;
	const vector<string> entries = { translate("New Game")
			       										 , translate("Load Game")
						      							 , translate("Settings")
								      					 , translate("Quit") };
};
