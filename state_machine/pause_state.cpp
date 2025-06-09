#include "game_state.h"

namespace state_machine {

sc::result Pause_state::react(const Input_event_start_button& event) {
	return transit<Play_state>();
}

sc::result Pause_state::react(const Game_event_quit& event) {
	context<Game_state_machine>().game_context.running = false;

	return discard_event();
}

Pause_state::Pause_state() {
	BOOST_LOG_TRIVIAL(debug) << "pauseState";
}

}