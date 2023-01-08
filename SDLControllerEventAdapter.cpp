#pragma once

#include "SDLControllerEventAdapter.h"

namespace adapter {
namespace sdl {
namespace controllerEvent {

event::ControllerButton getButton(Uint8 sdlButton) {
  switch (sdlButton) {
  case SDL_CONTROLLER_BUTTON_A:
    return event::A;
  case SDL_CONTROLLER_BUTTON_B:
    return event::B;
  case SDL_CONTROLLER_BUTTON_X:
    return event::X;
  case SDL_CONTROLLER_BUTTON_Y:
    return event::Y;
  case SDL_CONTROLLER_BUTTON_START:
    return event::START;
  }
}

event::ControllerButtonEvent
getControllerButtonEvent(SDL_Event* sdlEvent) {
  switch (sdlEvent->type) {
  case SDL_CONTROLLERBUTTONDOWN:
    return event::ControllerButtonEvent(getButton(sdlEvent->cbutton.button),
                                        event::PRESS);
  }
}

} // namespace event
} // namespace sdl
} // namespace adapters