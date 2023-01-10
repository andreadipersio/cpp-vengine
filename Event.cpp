#pragma once

#include "Event.h"

namespace event {
BaseEvent::BaseEvent(chrono::milliseconds timestamp)
    : timestamp(timestamp_), timestamp_(timestamp) {}

BaseControllerButtonEvent::BaseControllerButtonEvent(
    chrono::milliseconds timestamp, ControllerButton button)
    : BaseEvent(timestamp), button(button) {}

ControllerButtonPress::ControllerButtonPress(chrono::milliseconds timestamp,
                                             ControllerButton button)
    : BaseControllerButtonEvent(timestamp, button) {}
ControllerButtonRelease::ControllerButtonRelease(chrono::milliseconds timestamp,
                                                 ControllerButton button) : BaseControllerButtonEvent(timestamp, button) {}

} // namespace event