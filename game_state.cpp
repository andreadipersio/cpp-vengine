#include "game_state.h"

Game_state_machine::Game_state_machine(Game_context& gameContext) : game_context(gameContext) {
	gameContext.menu_manager.set_menu(menu::MENU_ID_MAIN);
}

sc::result Play_state::react(const Input_event_start_button& event) {
	return transit<Menu_state>();
}

Play_state::Play_state() {
	BOOST_LOG_TRIVIAL(debug) << "playState";
}

VisitEvent::VisitEvent(Game_state_machine& state_machine)
	: state_machine_(state_machine) {};

void VisitEvent::operator()(Menu_event_settings& event) {
	state_machine_.post_event_impl(event);
}

void VisitEvent::operator()(Menu_event_main& event) {
	state_machine_.post_event_impl(event);
}

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
