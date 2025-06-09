#include "game_state.h"

namespace state_machine {

Game_state_machine::Game_state_machine(Game_context& gameContext) : game_context(gameContext) {
	context<Game_state_machine>().game_context.state = Game_state::MENU;
	gameContext.menu_manager.set_menu(menu::MENU_ID_MAIN);
	gameContext.menu_manager.with_settings_menu_defaults("1024x768", "English");
}

Visit_event::Visit_event(Game_state_machine& state_machine)
	: state_machine_(state_machine) {};

void Visit_event::operator()(Menu_event_settings& event) {
	state_machine_.post_event_impl(event);
}

void Visit_event::operator()(Menu_event_main& event) {
	state_machine_.post_event_impl(event);
}

void Visit_event::operator()(Game_event_new_game& event) {
	state_machine_.post_event_impl(event);
}

void Visit_event::operator()(Game_event_quit& event) {
	state_machine_.post_event_impl(event);
}

Apply_choice::Apply_choice(Game_state_machine& state_machine)
	: state_machine_(state_machine) {};

void Apply_choice::operator()(menu::Choice_widget* widget) {
	Menu_event event = widget->current_choice()->apply();

	std::visit([&](auto event) {
		state_machine_.post_event_impl(event);
	}, event);
}

}
