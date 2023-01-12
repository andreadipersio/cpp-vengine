#pragma once

#include "SDLControllerEventAdapter.h"

namespace adapter {
namespace sdl {
namespace event {

::event::Event get(SDL_Event& sdlEvent) {
	switch (sdlEvent.type) {
	case SDL_CONTROLLERBUTTONDOWN: {
		auto button = getButton(sdlEvent.cbutton.button);
		milliseconds timestamp{ sdlEvent.cbutton.timestamp };

		auto event = ::event::ControllerButtonPress(timestamp, button);

		return ::event::Event(event);
	}

	case SDL_CONTROLLERBUTTONUP: {
		auto button = getButton(sdlEvent.cbutton.button);
		milliseconds timestamp{ sdlEvent.cbutton.timestamp };

		auto event = ::event::ControllerButtonRelease(timestamp, button);

		return ::event::Event(event);
	}

	}
}

::event::ControllerButton getButton(Uint8 sdlButton) {
	switch (sdlButton) {
	case SDL_CONTROLLER_BUTTON_A:
		return ::event::A;
	case SDL_CONTROLLER_BUTTON_B:
		return ::event::B;
	case SDL_CONTROLLER_BUTTON_X:
		return ::event::X;
	case SDL_CONTROLLER_BUTTON_Y:
		return ::event::Y;
	case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
		return ::event::LB;
	case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
		return ::event::RB;
	case SDL_CONTROLLER_BUTTON_START:
		return ::event::START;
	case SDL_CONTROLLER_BUTTON_BACK:
		return ::event::SELECT;
	}
}

} // namespace event
} // namespace sdl
} // namespace adapters