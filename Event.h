#pragma once

#include <chrono>
#include <variant>

namespace chrono = std::chrono;

namespace event {
enum ControllerButton { A, B, X, Y, LB, RB, LT, RT, START, SELECT };
enum ControllerEventType { PRESS, RELEASE };

enum EventType { CONTROLLER_BUTTON_DOWN, CONTROLLER_BUTTON_UP };

class BaseEvent {
public:
  const chrono::milliseconds& timestamp;

protected:
  BaseEvent(chrono::milliseconds);

private:
  chrono::milliseconds timestamp_;
};

class BaseControllerButtonEvent : public BaseEvent {
public:
  ControllerButton button;

protected:
  BaseControllerButtonEvent(chrono::milliseconds, ControllerButton);
};

class ControllerButtonPress : public BaseControllerButtonEvent {
public:
  ControllerButtonPress(chrono::milliseconds, ControllerButton);
};

class ControllerButtonRelease : public BaseControllerButtonEvent {
public:
  ControllerButtonRelease(chrono::milliseconds, ControllerButton);
};

using Event = std::variant<ControllerButtonPress, ControllerButtonRelease>;

} // namespace event
