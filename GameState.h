#pragma once

#include <boost/log/trivial.hpp>

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>

#include <boost/mpl/list.hpp>

#include "Events.h"
#include "GameContext.h"

namespace sc = boost::statechart;
namespace mpl = boost::mpl;

struct Menu_state;
struct Play_state;

struct Game_state_machine : sc::state_machine<Game_state_machine, Menu_state> {
	Game_context& gameContext;

	Game_state_machine(Game_context&);
};

struct Menu_state : sc::simple_state<Menu_state, Game_state_machine> {
	typedef mpl::list<
		sc::custom_reaction<Input_event_start_button>,
		sc::custom_reaction<Input_event_dpad_down>,
		sc::custom_reaction<Input_event_dpad_up>,
		sc::custom_reaction<Input_event_button_a>,
		sc::custom_reaction<Input_event_button_b>,
		sc::custom_reaction<Event_quit_game>
	> reactions;

	sc::result react(const Input_event_start_button&);
	sc::result react(const Input_event_dpad_down&);
	sc::result react(const Input_event_dpad_up&);
	sc::result react(const Input_event_button_a&);
	sc::result react(const Input_event_button_b&);
	sc::result react(const Event_quit_game& event);

	Menu_state();
};

struct Play_state : sc::simple_state<Play_state, Game_state_machine> {
	typedef  mpl::list<
		sc::custom_reaction<Input_event_start_button>
	> reactions;

	sc::result react(const Input_event_start_button&);

	Play_state();
};

struct VisitEvent {
	VisitEvent(Game_state_machine& state_machine);
	void operator()(Event_quit_game&);

private:
	Game_state_machine& state_machine_;
};

// https://github.com/CodeSports/State-Machine-Using-Boost-Statechart/tree/master/Chapter-2
