#include "GameState.h"

Game_state_machine::Game_state_machine(Game_context& gameContext) : gameContext(gameContext) {
	gameContext.menu_manager.set_menu(MENU_ID_MAIN);
}

sc::result Menu_state::react(const Input_event_start_button& event) {
	return transit<Play_state>();
}

sc::result Menu_state::react(const Input_event_dpad_down& event) {
	auto& menuManager = context<Game_state_machine>().gameContext.menu_manager;

	menuManager.next_menu_entry();
	menuManager.select_menu_entry();

	return discard_event();
}

sc::result Menu_state::react(const Input_event_dpad_up& event) {
	auto& menuManager = context<Game_state_machine>().gameContext.menu_manager;

	menuManager.prev_menu_entry();
	menuManager.select_menu_entry();

	return discard_event();
}

sc::result Menu_state::react(const Input_event_button_a& event) {
	auto& menuManager = context<Game_state_machine>().gameContext.menu_manager;

	if (auto subMenu = menuManager.has_submenu()) {
		menuManager.set_menu(subMenu.value());
	}

	if (auto& next_event = menuManager.get_menu_entry().game_event) {
		std::visit(VisitEvent(context<Game_state_machine>()), next_event.value());
	}

	return discard_event();
}

sc::result Menu_state::react(const Input_event_button_b& event) {
	auto& menuManager = context<Game_state_machine>().gameContext.menu_manager;

	menuManager.pop_menu();

	return discard_event();
}

sc::result Menu_state::react(const Event_quit_game& event) {
	context<Game_state_machine>().gameContext.running = false;

	return discard_event();
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

VisitEvent::VisitEvent(Game_state_machine& state_machine)
	: state_machine_(state_machine) {};

void VisitEvent::operator()(Event_quit_game& event) {
	state_machine_.post_event_impl(event);
}
