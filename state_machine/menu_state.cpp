#include "game_state.h"

namespace state_machine {

sc::result Menu_state::react(const Input_event_dpad_up& event) {
	auto& menu_manager = context<Game_state_machine>().game_context.menu_manager;

	menu_manager.prev_menu_entry();
	menu_manager.select_menu_entry();

	return discard_event();
}

sc::result Menu_state::react(const Input_event_dpad_down& event) {
	auto& menu_manager = context<Game_state_machine>().game_context.menu_manager;

	menu_manager.next_menu_entry();
	menu_manager.select_menu_entry();

	return discard_event();
}

sc::result Menu_state::react(const Input_event_button_a& event) {
	auto& menu_manager = context<Game_state_machine>().game_context.menu_manager;

	if (auto& next_event = menu_manager.get_menu_entry().game_event) {
		std::visit(Visit_event(context<Game_state_machine>()), next_event.value());
	}

	if (auto widget = menu_manager.get_menu_entry().widget) {
		std::visit(Apply_choice(context<Game_state_machine>()), widget.value());
	}

	return discard_event();
}

sc::result Menu_state::react(const Menu_event_settings& event) {
	auto& menu_manager = context<Game_state_machine>().game_context.menu_manager;

	menu_manager.set_menu(menu::MENU_ID_SETTINGS);
	return transit<Menu_settings_state>();
}

sc::result Menu_state::react(const Game_event_new_game& event) {
	return transit<Play_state>();
}

sc::result Menu_state::react(const Game_event_quit& event) {
	context<Game_state_machine>().game_context.running = false;

	return discard_event();
}

Menu_state::Menu_state() {
	BOOST_LOG_TRIVIAL(debug) << "menuState";
}

}
