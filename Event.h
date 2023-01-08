#pragma once

namespace event {
enum ControllerButton { A, B, X, Y, LB, RB, LT, RT, START, SELECT };
enum ControllerEventType { PRESS, RELEASE };

enum EventType { CONTROLLER_BUTTON_DOWN, CONTROLLER_BUTTON_UP };

class Event {
public:
  EventType type;

  Event(EventType);
};

class ControllerButtonEvent: public Event {
public:
  ControllerButton button;
  ControllerEventType controllerEventType;

  ControllerButtonEvent(ControllerButton, ControllerEventType);
};

}
