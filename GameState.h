#pragma once

#include <boost/log/trivial.hpp>

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>

#include <boost/mpl/list.hpp>

#include "GameContext.h"
#include "Input.h"

namespace sc = boost::statechart;
namespace mpl = boost::mpl;

struct menuState;
struct playState;

struct event_StartButton : sc::event<event_StartButton> {};
struct event_GameQuit : sc::event<event_GameQuit> {};

struct GameStateMachine : sc::state_machine<GameStateMachine, menuState> {
	GameContext& gameContext;

	GameStateMachine(GameContext&);
};

struct menuState : sc::simple_state<menuState, GameStateMachine> {
	typedef mpl::list<
		sc::custom_reaction<event_StartButton>,
		sc::custom_reaction<event_GameQuit>
	> reactions;

	sc::result react(const event_StartButton&);

	sc::result react(const event_GameQuit& event);

	menuState();
};

struct playState : sc::simple_state<playState, GameStateMachine> {
	typedef  mpl::list<
		sc::custom_reaction<event_StartButton>
	> reactions;

	sc::result react(const event_StartButton&);

	playState();
};

// https://github.com/CodeSports/State-Machine-Using-Boost-Statechart/tree/master/Chapter-2
