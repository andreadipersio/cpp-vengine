#include "menu.h"

namespace menu {

static const vector<choices::Base_choice*> resolution_choices = { 
	new choices::Resolution_choice(640, 480),
	new choices::Resolution_choice(800, 600), 
	new choices::Resolution_choice(1024, 768) 
};
static Choice_widget resolution_widget{ resolution_choices };

static const vector<choices::Base_choice*> language_choices = { 
	new choices::Language_choice(Language_id::DEUTSCH),
	new choices::Language_choice(Language_id::ENGLISH),
	new choices::Language_choice(Language_id::ITALIANO) 
};
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

void Menu_manager::with_settings_menu_defaults(string resolution, string language) {
	auto& settings_menu = menus_[MENU_ID_SETTINGS];

	for (auto i = 0; i < settings_menu->entries.size(); i++) {
		auto& entry = settings_menu->entries[i];
		auto& widget = entry.widget;

		if (!widget) {
			continue;
		}

		if (entry.id == "Resolution")
			std::visit(Widget_defaul_value_visitor(resolution), widget.value());
		else if (entry.id == "Language")
			std::visit(Widget_defaul_value_visitor(language), widget.value());
	}
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

Widget_defaul_value_visitor::Widget_defaul_value_visitor(string default_value)
	: default_value_(default_value) {}

void Widget_defaul_value_visitor::operator()(menu::Choice_widget* widget) {
	while (!widget->is_last()) {
		if (widget->current_choice()->label() == default_value_) {
			return;
		} 

		widget->next_choice();
	}
}

} // end namespace
