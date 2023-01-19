#include "GameState.h"

GameStateMachine::GameStateMachine(GameContext& gameContext) : gameContext(gameContext) {
	BOOST_LOG_TRIVIAL(debug) << "Welcome to the machine";
}

sc::result menuState::react(const inputEvent_StartButton& event) {
	return transit<playState>();
}

sc::result menuState::react(const inputEvent_DPadDown& event) {
	auto& menu = context<GameStateMachine>().gameContext.menu;

	BOOST_LOG_TRIVIAL(debug) << "From " << menu.currentEntry() << " to " << menu.nextEntry();

	return forward_event();
}

sc::result menuState::react(const inputEvent_DPadUp& event) {
	auto& menu = context<GameStateMachine>().gameContext.menu;

	BOOST_LOG_TRIVIAL(debug) << "From " << menu.currentEntry() << " to " << menu.previousEntry();

	return forward_event();
}

sc::result menuState::react(const event_GameQuit& event) {
	context<GameStateMachine>().gameContext.running = false;

	BOOST_LOG_TRIVIAL(debug) << "handling event_GameQuit";

	return forward_event();
}

menuState::menuState() {
	BOOST_LOG_TRIVIAL(debug) << "menuState";
}

sc::result playState::react(const inputEvent_StartButton& event) {
	return transit<menuState>();
}

playState::playState() {
	BOOST_LOG_TRIVIAL(debug) << "playState";
}
