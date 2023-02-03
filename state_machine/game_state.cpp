#include "game_state.h"

namespace state_machine {

Game_state_machine::Game_state_machine(Game_context& gameContext) : game_context(gameContext) {
	gameContext.menu_manager.set_menu(menu::MENU_ID_MAIN);
	gameContext.menu_manager.with_settings_menu_defaults("1024x768", "English");
}

sc::result Play_state::react(const Input_event_start_button& event) {
	return transit<Menu_state>();
}

Play_state::Play_state() {
	BOOST_LOG_TRIVIAL(debug) << "playState";
}

Visit_event::Visit_event(Game_state_machine& state_machine)
	: state_machine_(state_machine) {};

void Visit_event::operator()(Menu_event_settings& event) {
	state_machine_.post_event_impl(event);
}

void Visit_event::operator()(Menu_event_main& event) {
	state_machine_.post_event_impl(event);
}

void Visit_event::operator()(Game_event_quit& event) {
	state_machine_.post_event_impl(event);
}

Visit_widget::Visit_widget(Game_state_machine& state_machine)
	: state_machine_(state_machine) {};

void Visit_widget::operator()(menu::Choice_widget* widget) {
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

}
