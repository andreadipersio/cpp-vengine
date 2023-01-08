#pragma once

#include <variant>

namespace event {
enum ControllerButton { A, B, X, Y, LB, RB, LT, RT, START, SELECT };
enum ControllerEventType { PRESS, RELEASE };

enum EventType { CONTROLLER_BUTTON_DOWN, CONTROLLER_BUTTON_UP };

class ControllerButtonPress {
public:
  ControllerButton button;

  ControllerButtonPress(ControllerButton);
};

class ControllerButtonRelease {
public:
  ControllerButton button;

  ControllerButtonRelease(ControllerButton);
};

using Event = std::variant<ControllerButtonPress, ControllerButtonRelease>;

}
