#pragma once

#include "Event.h"

namespace event {

  Event::Event(EventType type) : type(type) {}

  ControllerButtonEvent::ControllerButtonEvent(ControllerButton button, ControllerEventType type)
      : Event(CONTROLLER_BUTTON_DOWN), button(button), controllerEventType(type) {}

}