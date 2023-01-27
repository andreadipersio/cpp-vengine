#include "GameState.h"

Game_state_machine::Game_state_machine(Game_context& gameContext) : game_context(gameContext) {
	gameContext.menu_manager.set_menu(MENU_ID_MAIN);
}

sc::result Menu_state::react(const Input_event_start_button& event) {
	return transit<Play_state>();
}

sc::result Menu_state::react(const Input_event_dpad_up& event) {
	auto& menuManager = context<Game_state_machine>().game_context.menu_manager;

	menuManager.prev_menu_entry();
	menuManager.select_menu_entry();

	return discard_event();
}

sc::result Menu_state::react(const Input_event_dpad_left& event) {
	auto& menuManager = context<Game_state_machine>().game_context.menu_manager;

	if (auto widget = menuManager.get_menu_entry().widget) {
		std::visit([](Menu_widget_choice* choice) {
			choice->prev_choice();
		}, widget.value());
	}

	return discard_event();
}

sc::result Menu_state::react(const Input_event_dpad_down& event) {
	auto& menuManager = context<Game_state_machine>().game_context.menu_manager;

	menuManager.next_menu_entry();
	menuManager.select_menu_entry();

	return discard_event();
}

sc::result Menu_state::react(const Input_event_dpad_right& event) {
	auto& menuManager = context<Game_state_machine>().game_context.menu_manager;

	if (auto widget = menuManager.get_menu_entry().widget) {
		std::visit([](Menu_widget_choice* choice) {
			choice->next_choice();
		}, widget.value());
	}

	return discard_event();
}

sc::result Menu_state::react(const Input_event_button_a& event) {
	auto& menuManager = context<Game_state_machine>().game_context.menu_manager;

	if (auto subMenu = menuManager.has_submenu()) {
		menuManager.set_menu(subMenu.value());
	}

	if (auto& next_event = menuManager.get_menu_entry().game_event) {
		std::visit(VisitEvent(context<Game_state_machine>()), next_event.value());
	}

	if (auto widget = menuManager.get_menu_entry().widget) {
		std::visit(VisitWidget(context<Game_state_machine>()), widget.value());
	}

	return discard_event();
}

sc::result Menu_state::react(const Input_event_button_b& event) {
	auto& menuManager = context<Game_state_machine>().game_context.menu_manager;

	menuManager.pop_menu();

	return discard_event();
}

sc::result Menu_state::react(const Menu_event_change_resolution& event) {
	auto& settings = context<Game_state_machine>().game_context.settings;

	settings.set_resolution(event.width, event.height);

	return discard_event();
}

sc::result Menu_state::react(const Game_event_quit& event) {
	context<Game_state_machine>().game_context.running = false;

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

void VisitEvent::operator()(Game_event_quit& event) {
	state_machine_.post_event_impl(event);
}

VisitWidget::VisitWidget(Game_state_machine& state_machine)
	: state_machine_(state_machine) {};

void VisitWidget::operator()(Menu_widget_choice* widget) {
	vector<std::tuple<string, uint16_t, uint16_t>> video_modes{
		{"640x480", 640, 480},
		{"800x600", 800, 600},
		{"1024x768", 1024, 768}
	};

	for (auto [resolution_str, width, height] : video_modes) {
		if (widget->current_choice() != resolution_str) continue;
		state_machine_.post_event_impl(Menu_event_change_resolution{ width, height });
		break;
	}
}
