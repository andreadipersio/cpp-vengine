#include "game_state.h"

sc::result Menu_settings_state::react(const Input_event_dpad_up& event) {
	auto& menu_manager = context<Game_state_machine>().game_context.menu_manager;

	menu_manager.prev_menu_entry();
	menu_manager.select_menu_entry();

	return discard_event();
}

sc::result Menu_settings_state::react(const Input_event_dpad_left& event) {
	auto& menu_manager = context<Game_state_machine>().game_context.menu_manager;

	if (auto widget = menu_manager.get_menu_entry().widget) {
		std::visit([](Menu_widget_choice* choice) {
			choice->prev_choice();
		}, widget.value());
	}

	return discard_event();
}

sc::result Menu_settings_state::react(const Input_event_dpad_down& event) {
	auto& menu_manager = context<Game_state_machine>().game_context.menu_manager;

	menu_manager.next_menu_entry();
	menu_manager.select_menu_entry();

	return discard_event();
}

sc::result Menu_settings_state::react(const Input_event_dpad_right& event) {
	auto& menu_manager = context<Game_state_machine>().game_context.menu_manager;

	if (auto widget = menu_manager.get_menu_entry().widget) {
		std::visit([](Menu_widget_choice* choice) {
			choice->next_choice();
		}, widget.value());
	}

	return discard_event();
}

sc::result Menu_settings_state::react(const Input_event_button_a& event) {
	auto& menu_manager = context<Game_state_machine>().game_context.menu_manager;

	if (auto& next_event = menu_manager.get_menu_entry().game_event) {
		std::visit(VisitEvent(context<Game_state_machine>()), next_event.value());
	}

	if (auto widget = menu_manager.get_menu_entry().widget) {
		std::visit(VisitWidget(context<Game_state_machine>()), widget.value());
	}

	return discard_event();
}

sc::result Menu_settings_state::react(const Input_event_button_b& event) {
	auto& menu_manager = context<Game_state_machine>().game_context.menu_manager;

	return discard_event();
}

sc::result Menu_settings_state::react(const Menu_event_change_resolution& event) {
	auto& settings = context<Game_state_machine>().game_context.settings;

	settings.set_resolution(event.width, event.height);

	return discard_event();
}

sc::result Menu_settings_state::react(const Menu_event_main& event) {
	auto& menu_manager = context<Game_state_machine>().game_context.menu_manager;

	menu_manager.set_menu(menu::MENU_ID_MAIN);
	return transit<Menu_state>();
}

Menu_settings_state::Menu_settings_state() {
	BOOST_LOG_TRIVIAL(debug) << "menuSettingsState";
}
