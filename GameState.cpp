#include "GameState.h"

Game_state_machine::Game_state_machine(Game_context& gameContext) : gameContext(gameContext) {
	BOOST_LOG_TRIVIAL(debug) << "Welcome to the machine";

	gameContext.menu_manager.set_menu(MENU_ID_MAIN);
}

sc::result Menu_state::react(const Input_event_start_button& event) {
	return transit<Play_state>();
}

sc::result Menu_state::react(const Input_event_dpad_down& event) {
	auto& menuManager = context<Game_state_machine>().gameContext.menu_manager;

	menuManager.next_menu_entry();
	menuManager.select_menu_entry();

	BOOST_LOG_TRIVIAL(debug) << menuManager.get_menu_entry();

	return forward_event();
}

sc::result Menu_state::react(const Input_event_dpad_up& event) {
	auto& menuManager = context<Game_state_machine>().gameContext.menu_manager;

	menuManager.prev_menu_entry();
	menuManager.select_menu_entry();

	BOOST_LOG_TRIVIAL(debug) << menuManager.get_menu_entry();

	return forward_event();
}

sc::result Menu_state::react(const Input_event_button_a& event) {
	auto& menuManager = context<Game_state_machine>().gameContext.menu_manager;

	if (auto subMenu = menuManager.has_submenu()) {
		menuManager.set_menu(subMenu.value());
	}

	return forward_event();
}

sc::result Menu_state::react(const Event_quit_game& event) {
	context<Game_state_machine>().gameContext.running = false;

	BOOST_LOG_TRIVIAL(debug) << "handling event_GameQuit";

	return forward_event();
}

Menu_state::Menu_state() {
	BOOST_LOG_TRIVIAL(debug) << "menuState";
}

sc::result Play_state::react(const Input_event_start_button& event) {
	return transit<Menu_state>();
}

Play_state::Play_state() {
	BOOST_LOG_TRIVIAL(debug) << "playState";
}
