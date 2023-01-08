#pragma once

#include "Event.h"

namespace event {

  ControllerButtonPress::ControllerButtonPress(ControllerButton button)
      : button(button) {}

  ControllerButtonRelease::ControllerButtonRelease(ControllerButton button)
      : button(button) {}
}