#pragma once

#include <boost/statechart/event.hpp>
#include <variant>

namespace sc = boost::statechart;

struct Input_event_start_button : sc::event<Input_event_start_button> {};
struct Input_event_dpad_up: sc::event<Input_event_dpad_up> {};
struct Input_event_dpad_right: sc::event<Input_event_dpad_right> {};
struct Input_event_dpad_down: sc::event<Input_event_dpad_down> {};
struct Input_event_dpad_left: sc::event<Input_event_dpad_left> {};
struct Input_event_button_a: sc::event<Input_event_button_a> {};
struct Input_event_button_b: sc::event<Input_event_button_b> {};

struct Game_event_quit : sc::event<Game_event_quit> {};

struct Menu_event_change_resolution: sc::event<Menu_event_change_resolution> {
	uint16_t width;
	uint16_t height;

	Menu_event_change_resolution(uint16_t, uint16_t);
};

using Input_event = std::variant< Input_event_start_button
	                              , Input_event_dpad_down
																, Input_event_dpad_up
																, Input_event_button_a
																, Input_event_button_b 
                                >;

using Game_event = std::variant<Game_event_quit>;
