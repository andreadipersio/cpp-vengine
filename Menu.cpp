#include "Menu.h"

namespace menu {

static const vector<string> resolution_choices = { "640x480", "800x600", "1024x768" };
static Choice_widget resolution_widget{ resolution_choices };

static const vector<string> language_choices = { "English", "Italiano", "Deutsch" };
static Choice_widget language_widget{ language_choices };

static const vector<Menu_entry> main_menu_entries = {
	{"New Game", true},
	{"Load Game", false},
	{"Settings", false, Menu_event_settings{}},
	{"Quit Game", false, Game_event_quit{}}
};

static const vector<Menu_entry> settings_menu_entries = {
	{"Resolution", true, nullopt, Menu_widget{&resolution_widget}},
	{"Language", false, nullopt, Menu_widget{&language_widget}},
	{"Controls", false},
	{"Back", false, Menu_event_main{}}
};

Menu::Menu(Menu_id id, vector<Menu_entry> entries) : id(id), entries(entries) {};

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

Menu_manager::Menu_manager() : current_menu_(nullptr) {
	menus_[MENU_ID_MAIN] = new Menu{ MENU_ID_MAIN, main_menu_entries };
	menus_[MENU_ID_SETTINGS] = new Menu{ MENU_ID_SETTINGS, settings_menu_entries };
}

void Menu_manager::set_menu(Menu_id menu_id) {
	current_menu_ = menus_[menu_id];
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

std::ostream& operator<<(std::ostream& os, Menu_entry& menu_entry) {
	if (menu_entry.is_selected)
		return os << "Menu Entry: " << menu_entry.id << " [SELECTED]";
	else
		return os << "Menu Entry: " << menu_entry.id;
}

}
