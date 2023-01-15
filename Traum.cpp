#include <fmt/core.h>
#include <iostream>
#include <boost/log/trivial.hpp>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "GameContext.h"
#include "Input.h"
#include "SDLControllerEventAdapter.h"

using fmt::format;

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) {
		BOOST_LOG_TRIVIAL(fatal) << format("SDL_Init Error: {}", SDL_GetError());
	}


	SDL_Window* win = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED,
																		 SDL_WINDOWPOS_CENTERED, 800, 600, 0);

	GameContext gc;

	gc.actionSet = new input::MenuActionSet;

	bool run = true;

	while (run) {
		SDL_Event sdlEvent;

		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
			case SDL_QUIT:
				run = false;
				break;
			case SDL_CONTROLLERDEVICEADDED: {
				auto controllerId = sdlEvent.cdevice.which;
				BOOST_LOG_TRIVIAL(info) << format(
					"Controller with id '{}' has been detected", controllerId);
				SDL_GameControllerOpen(controllerId);
				auto controller = SDL_GameControllerFromInstanceID(controllerId);
				if (controller) {
					gc.controllers[(int32_t)controllerId] = controller;
				} else {
					BOOST_LOG_TRIVIAL(warning)
						<< format("Controller with id '{}' could not be opened: {}",
											controllerId, SDL_GetError());
				}
				break;
			}
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
				if (sdlEvent.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
					switch (gc.actionSet->id()) {
					case input::GAME_ACTION_SET:
						BOOST_LOG_TRIVIAL(debug) << "Activating MenuActionSet";
						gc.actionSet = new input::MenuActionSet;
						break;
					case input::MENU_ACTION_SET:
						BOOST_LOG_TRIVIAL(debug) << "Activating GameActionSet";
						gc.actionSet = new input::GameActionSet;
						break;
					}
				} else {
					auto event = adapter::sdl::event::get(sdlEvent);
					if (auto command = gc.actionSet->handleInput(&event)) {
						command->execute();
					}
				}
				break;
			case SDL_KEYDOWN:
				SDL_Event quitEvent = { SDL_QUIT };
				BOOST_LOG_TRIVIAL(debug) << format("FPS: {}", gc.clock.fps());

				switch (sdlEvent.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					SDL_PushEvent(&quitEvent);
				}
				break;
			}
		}

		gc.clock.atFrameStart();
		SDL_Delay(16);
		gc.clock.atFrameEnd();
	}



	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}
