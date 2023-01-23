#pragma once

#include <boost/statechart/event.hpp>
#include <variant>

namespace sc = boost::statechart;

struct Input_event_start_button : sc::event<Input_event_start_button> {};
struct Input_event_dpad_down: sc::event<Input_event_dpad_down> {};
struct Input_event_dpad_up: sc::event<Input_event_dpad_up> {};
struct Input_event_button_a: sc::event<Input_event_button_a> {};
struct Input_event_button_b: sc::event<Input_event_button_b> {};

struct Event_quit_game : sc::event<Event_quit_game> {};

using Input_event = std::variant< Input_event_start_button
	                              , Input_event_dpad_down
																, Input_event_dpad_up
																, Input_event_button_a
																, Input_event_button_b 
                                >;

using Game_event = std::variant<Event_quit_game>;
