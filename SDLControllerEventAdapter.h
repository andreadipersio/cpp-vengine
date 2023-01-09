#pragma once

#include "Event.h"
#include <SDL2/SDL.h>

namespace adapter {
namespace sdl {
namespace event {

::event::Event get(SDL_Event*); 
::event::ControllerButton getButton(Uint8);

} // namespace event
} // namespace sdl
} // namespace adapters

