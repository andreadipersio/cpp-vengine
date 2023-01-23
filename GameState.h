#pragma once

#include <boost/log/trivial.hpp>

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>

#include <boost/mpl/list.hpp>

#include "GameContext.h"

namespace sc = boost::statechart;
namespace mpl = boost::mpl;

struct Menu_state;
struct Play_state;

struct Input_event_start_button : sc::event<Input_event_start_button> {};
struct Input_event_dpad_down: sc::event<Input_event_dpad_down> {};
struct Input_event_dpad_up: sc::event<Input_event_dpad_up> {};
struct Input_event_button_a: sc::event<Input_event_button_a> {};

struct Event_quit_game : sc::event<Event_quit_game> {};

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
		sc::custom_reaction<Event_quit_game>
	> reactions;

	sc::result react(const Input_event_start_button&);
	sc::result react(const Input_event_dpad_down&);
	sc::result react(const Input_event_dpad_up&);
	sc::result react(const Input_event_button_a&);
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

// https://github.com/CodeSports/State-Machine-Using-Boost-Statechart/tree/master/Chapter-2
