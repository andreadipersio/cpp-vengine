#include "Menu.h"

vector<Menu_entry> mainMenuEntries = {
	{"New Game", true, nullopt},
	{"Load Game", false, nullopt},
	{"Settings", false, MENU_ID_SETTINGS},
	{"Quit Game", false, nullopt}
};

vector<Menu_entry> settingsMenuEntries = {
	{"Resolution", true, nullopt},
	{"Language", false, nullopt},
	{"Controls", false, nullopt},
	{"Back", false, MENU_ID_MAIN}
};

Menu::Menu(vector<Menu_entry> entries) : entries(entries) {};

Menu_entry& Menu::next_entry() {
	if (index < entries.size() - 1) {
		index++;
	}

	return current_entry();
}

Menu_entry& Menu::prev_entry() {
	if (index != 0) {
		index--;
	}

	return current_entry();
}

Menu_entry& Menu::current_entry() {
	return entries[index];
}

Menu_entry& Menu_manager::get_menu_entry() {
	return current_menu_->current_entry();
}

void Menu::select() {
	for (auto i = 0; i < entries.size(); i++) {
		if (auto& entry = entries[i]; i == index)
			entry.is_selected = true;
		else
			entry.is_selected = false;
	}
}

Menu_manager::Menu_manager() {
	menus_[MENU_ID_MAIN] = new Menu{mainMenuEntries};
	menus_[MENU_ID_SETTINGS] = new Menu{settingsMenuEntries};
}

void Menu_manager::set_menu(Menu_id menuId) {
	current_menu_ = menus_[menuId];
}

vector<Menu_entry>::iterator Menu_manager::begin() {
	return current_menu_->entries.begin();
}

vector<Menu_entry>::iterator Menu_manager::end() {
	return current_menu_->entries.end();
}

void Menu_manager::next_menu_entry() {
	current_menu_->next_entry();
}

void Menu_manager::prev_menu_entry() {
	current_menu_->prev_entry();
}

void Menu_manager::select_menu_entry() {
	for (auto i = 0; i < current_menu_->entries.size(); i++) {
		if (auto& entry = current_menu_->entries[i]; i == current_menu_->index)
			entry.is_selected = true;
		else
			entry.is_selected = false;
	}
}

optional<Menu_id> Menu_manager::has_submenu() {
	return current_menu_->current_entry().next_menu;
}

std::ostream& operator<<(std::ostream& os, Menu_entry& menuEntry) {
	if (menuEntry.is_selected)
		return os << "Menu Entry: " << menuEntry.id << " [SELECTED]";
	else
		return os << "Menu Entry: " << menuEntry.id;
}

