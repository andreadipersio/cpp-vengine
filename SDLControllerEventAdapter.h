#pragma once

#include "Event.h"
#include <SDL2/SDL.h>

namespace adapter {
namespace sdl {
namespace controllerEvent {

event::ControllerButton getButton(Uint8);
event::Event get(SDL_Event*); 

} // namespace event
} // namespace sdl
} // namespace adapters

