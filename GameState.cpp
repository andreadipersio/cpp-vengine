#include "GameState.h"

GameStateMachine::GameStateMachine(GameContext& gameContext) : gameContext(gameContext) {
	BOOST_LOG_TRIVIAL(debug) << "Welcome to the machine";
}

sc::result menuState::react(const event_StartButton& event) {
	context<GameStateMachine>().gameContext.actionSet = new input::GameActionSet;

	return transit<playState>();
}

sc::result menuState::react(const event_GameQuit& event) {
	context<GameStateMachine>().gameContext.running = false;

	BOOST_LOG_TRIVIAL(debug) << "handling event_GameQuit";

	return forward_event();
}

menuState::menuState() {
	BOOST_LOG_TRIVIAL(debug) << "menuState";
}

sc::result playState::react(const event_StartButton& event) {
	context<GameStateMachine>().gameContext.actionSet = new input::MenuActionSet;

	return transit<menuState>();
}

playState::playState() {
	BOOST_LOG_TRIVIAL(debug) << "playState";
}
