#pragma once

#include "Event.h"

namespace event {
ostream& operator<<(ostream& os, ControllerButton button) {
	switch (button) {
	case A:
		os << "<A>";
		break;
	case B:
		os << "<B>";
		break;
	case X:
		os << "<X>";
		break;
	case Y:
		os << "<Y>";
		break;
	case LB:
		os << "<LB>";
		break;
	case LT:
		os << "<LT>";
		break;
	case RB: 
		os << "<RB>";
		break;
	case RT:
		os << "<RT>";
		break;
	case START:
		os << "<START>";
		break;
	case SELECT:
		os << "<SELECT>";
		break;
	}

	return os;
}

BaseEvent::BaseEvent(milliseconds timestamp)
	: timestamp_(timestamp) {
}

milliseconds BaseEvent::timestamp() const {
	return timestamp_;
}

BaseControllerButtonEvent::BaseControllerButtonEvent(
	milliseconds timestamp, ControllerButton button)
	: BaseEvent(timestamp), button(button) {
}

ControllerButtonPress::ControllerButtonPress(milliseconds timestamp,
																						 ControllerButton button)
	: BaseControllerButtonEvent(timestamp, button) {
}
ControllerButtonRelease::ControllerButtonRelease(milliseconds timestamp,
																								 ControllerButton button) 
	: BaseControllerButtonEvent(timestamp, button) {
}

} // namespace event