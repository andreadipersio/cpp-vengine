#pragma once

#include "Event.cpp"
#include <SDL2/SDL.h>

namespace adapter {
namespace sdl {
namespace controllerEvent {

event::ControllerButton getButton(Uint8);
event::ControllerButtonEvent getControllerButtonEvent(SDL_Event*); 

} // namespace event
} // namespace sdl
} // namespace adapters

