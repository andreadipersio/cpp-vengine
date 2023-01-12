#pragma once

#include <chrono>
#include <iostream>
#include <variant>

using std::ostream;
using std::chrono::milliseconds;

namespace event {
enum ControllerButton {
	A, B, X, Y, LB, RB, LT, RT, START, SELECT
};

ostream& operator<<(ostream&, ControllerButton);

enum ControllerEventType {
	PRESS, RELEASE
};

enum EventType {
	CONTROLLER_BUTTON_DOWN, CONTROLLER_BUTTON_UP
};

class BaseEvent {
public:
	milliseconds timestamp() const;

protected:
	BaseEvent(milliseconds);

private: 
	milliseconds timestamp_;
};

class BaseControllerButtonEvent : public BaseEvent {
public:
	ControllerButton button;

protected:
	BaseControllerButtonEvent(milliseconds, ControllerButton);
};

class ControllerButtonPress : public BaseControllerButtonEvent {
public:
	ControllerButtonPress(milliseconds, ControllerButton);
};

class ControllerButtonRelease : public BaseControllerButtonEvent {
public:
	ControllerButtonRelease(milliseconds, ControllerButton);
};

using Event = std::variant<ControllerButtonPress, ControllerButtonRelease>;

} // namespace event
