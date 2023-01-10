#pragma once

#include <chrono>

#include <SDL2/SDL.h>

#include "Event.h"

namespace chrono = std::chrono;

namespace adapter {
namespace sdl {
namespace event {

::event::Event get(SDL_Event*); 
::event::ControllerButton getButton(Uint8);

} // namespace event
} // namespace sdl
} // namespace adapters

