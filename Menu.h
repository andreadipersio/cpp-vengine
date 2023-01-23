#pragma once

#include <array>
#include <boost/log/trivial.hpp>
#include <boost/locale.hpp>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "Events.h"

using std::array;
using std::vector;
using std::string;
using std::optional, std::nullopt;
using boost::locale::translate;

enum Menu_id {
	MENU_ID_MAIN,
	MENU_ID_SETTINGS
};

const int MENU_COUNT = 2;

struct Menu_entry {
	string id;
	bool is_selected;
	optional<Menu_id> next_menu;
	optional<Game_event> game_event;
};

class Menu {
public:
	Menu_entry& next_entry();
	Menu_entry& prev_entry();
	Menu_entry& current_entry();
	void select();

	unsigned int index = 0;

	Menu_id id;
	vector<Menu_entry> entries;

public:
	Menu(Menu_id, vector<Menu_entry>);
};

class Menu_manager {
public:
	Menu_manager();

	vector<Menu_entry>::iterator begin();
	vector<Menu_entry>::iterator end();

	void next_menu_entry();
	void prev_menu_entry();
	void select_menu_entry();
	Menu_entry& get_menu_entry();

	void set_menu(Menu_id menuId);
	void push_menu(Menu_id menuId);
	void pop_menu();

	optional<Menu_id> has_submenu();

private:
	array<Menu*, MENU_COUNT> menus_;
	vector<Menu*> breadcrumbs_;

	Menu* current_menu_;
};

std::ostream& operator<<(std::ostream& os, Menu_entry& menuEntry);
