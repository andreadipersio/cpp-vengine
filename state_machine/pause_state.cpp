#include "game_state.h"

namespace state_machine {

sc::result Pause_state::react(const Input_event_start_button& event) {
	context<Game_state_machine>().game_context.state = Game_state::PLAY;
	return transit<Play_state>();
}

sc::result Pause_state::react(const Game_event_quit& event) {
	context<Game_state_machine>().game_context.state = Game_state::QUIT;

	return discard_event();
}

Pause_state::Pause_state() {
	BOOST_LOG_TRIVIAL(debug) << "pauseState";
}

}