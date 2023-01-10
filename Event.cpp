#pragma once

#include "Event.h"

namespace event {
BaseEvent::BaseEvent(milliseconds timestamp)
    : timestamp(timestamp_), timestamp_(timestamp) {}

BaseControllerButtonEvent::BaseControllerButtonEvent(
    milliseconds timestamp, ControllerButton button)
    : BaseEvent(timestamp), button(button) {}

ControllerButtonPress::ControllerButtonPress(milliseconds timestamp,
                                             ControllerButton button)
    : BaseControllerButtonEvent(timestamp, button) {}
ControllerButtonRelease::ControllerButtonRelease(milliseconds timestamp,
                                                 ControllerButton button) : BaseControllerButtonEvent(timestamp, button) {}

} // namespace event