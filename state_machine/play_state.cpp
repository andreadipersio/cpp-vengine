#include "game_state.h"

namespace state_machine {

sc::result Play_state::react(const Input_event_start_button& event) {
	context<Game_state_machine>().game_context.state = Game_state::PAUSE;
	return transit<Pause_state>();
}

sc::result Play_state::react(const Game_event_quit& event) {
	context<Game_state_machine>().game_context.state = Game_state::QUIT;

	return discard_event();
}

Play_state::Play_state() {
	BOOST_LOG_TRIVIAL(debug) << "playState";
}

}