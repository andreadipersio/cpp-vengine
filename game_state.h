#pragma once

#include <ranges>
#include <tuple>
#include <boost/log/trivial.hpp>
#include <functional>

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>

#include <boost/mpl/list.hpp>

#include "events.h"
#include "game_context.h"
#include "menu_widget.h"

namespace sc = boost::statechart;
namespace mpl = boost::mpl;

using std::reference_wrapper;

struct Menu_state;
struct Menu_settings_state;
struct Play_state;

struct Game_state_machine : sc::state_machine<Game_state_machine, Menu_state> {
	Game_context& game_context;

	Game_state_machine(Game_context&);
};

struct Menu_state : sc::simple_state<Menu_state, Game_state_machine> {
	typedef mpl::list<
		sc::custom_reaction<Input_event_dpad_up>,
		sc::custom_reaction<Input_event_dpad_down>,
		sc::custom_reaction<Input_event_button_a>,
		sc::custom_reaction<Game_event_quit>,
		sc::custom_reaction<Menu_event_settings>
	> reactions;

	sc::result react(const Input_event_dpad_up&);
	sc::result react(const Input_event_dpad_down&);
	sc::result react(const Input_event_button_a&);
	sc::result react(const Menu_event_settings&);
	sc::result react(const Game_event_quit&);

	Menu_state();
};

struct Menu_settings_state : sc::simple_state<Menu_settings_state, Game_state_machine> {
	typedef mpl::list<
		sc::custom_reaction<Input_event_dpad_up>,
		sc::custom_reaction<Input_event_dpad_right>,
		sc::custom_reaction<Input_event_dpad_down>,
		sc::custom_reaction<Input_event_dpad_left>,
		sc::custom_reaction<Input_event_button_a>,
		sc::custom_reaction<Input_event_button_b>,
		sc::custom_reaction<Menu_event_change_resolution>,
		sc::custom_reaction<Menu_event_main>
	> reactions;

	sc::result react(const Input_event_dpad_up&);
	sc::result react(const Input_event_dpad_right&);
	sc::result react(const Input_event_dpad_down&);
	sc::result react(const Input_event_dpad_left&);
	sc::result react(const Input_event_button_a&);
	sc::result react(const Input_event_button_b&);
	sc::result react(const Menu_event_change_resolution&);
	sc::result react(const Menu_event_main&);

	Menu_settings_state();
};

struct Play_state : sc::simple_state<Play_state, Game_state_machine> {
	typedef  mpl::list<
		sc::custom_reaction<Input_event_start_button>
	> reactions;

	sc::result react(const Input_event_start_button&);

	Play_state();
};

struct VisitEvent {
public:
	VisitEvent(Game_state_machine&);
	void operator()(Menu_event_settings&);
	void operator()(Menu_event_main&);
	void operator()(Game_event_quit&);
private:
	Game_state_machine& state_machine_;
};

struct VisitWidget {
public:
	VisitWidget(Game_state_machine&);
	void operator()(menu::Choice_widget*);
private:
	Game_state_machine& state_machine_;
};

// https://github.com/CodeSports/State-Machine-Using-Boost-Statechart/tree/master/Chapter-2
