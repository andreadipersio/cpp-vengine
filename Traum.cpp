#include <fmt/core.h>
#include <iostream>
#include <boost/log/trivial.hpp>

#include <utility>
#include <array>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "GameContext.h"
#include "GameState.h"

using fmt::format;

// Credits:
// https://swarminglogic.com/scribble/2015_05_smartwrappers
namespace sdl2 {
struct SDL_Deleter {
	void operator()(SDL_Surface* ptr) {
		if (ptr) SDL_FreeSurface(ptr);
	}

	void operator()(SDL_Texture* ptr) {
		if (ptr) SDL_DestroyTexture(ptr);
	}
};

using SurfacePtr = std::unique_ptr<SDL_Surface, SDL_Deleter>;
using TexturePtr = std::unique_ptr<SDL_Texture, SDL_Deleter>;
}

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) {
		BOOST_LOG_TRIVIAL(fatal) << format("SDL_Init Error: {}", SDL_GetError());
	}

	if (TTF_Init() != 0) {
		BOOST_LOG_TRIVIAL(fatal) << format("TTF_Init Error: {}", TTF_GetError());
	}

	TTF_Font* menuFont = TTF_OpenFont("F:/projects/Traum/Traum/MenuFont.ttf", 24);

	if (!menuFont) {
		BOOST_LOG_TRIVIAL(fatal) << format("Cannot load font: {}", TTF_GetError());
		return 1;
	}


	SDL_Window* win = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED,
																		 SDL_WINDOWPOS_CENTERED, 800, 600, 0);

	SDL_Renderer* r = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	if (!r) {
		BOOST_LOG_TRIVIAL(fatal) << format("SDL_CreateRenderer Error: {}", SDL_GetError());
		return 1;
	}

	GameContext gc{};

	GameStateMachine gameStateMachine{ gc };
	gameStateMachine.initiate();

	while (gc.running) {
		SDL_Event sdlEvent;

		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
			case SDL_QUIT:
				gameStateMachine.process_event(event_GameQuit());
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
				switch (sdlEvent.cbutton.button) {
				case SDL_CONTROLLER_BUTTON_START:
					gameStateMachine.process_event(inputEvent_StartButton{});
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
					gameStateMachine.process_event(inputEvent_DPadDown{});
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_UP:
					gameStateMachine.process_event(inputEvent_DPadUp{});
					break;
				case SDL_CONTROLLER_BUTTON_A:
					break;
				}
			case SDL_CONTROLLERBUTTONUP:
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


		SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
		SDL_RenderClear(r);

		///
		for (auto i = 0; i < gc.menu.entries.size(); i++) {
			auto menuEntry = gc.menu.entries[i];

			SDL_Color color;
			if (gc.menu.index == i) {
				color = { 238, 75, 43 };
			} else {
				color = { 255, 255, 255 };
			}

			sdl2::SurfacePtr surface{TTF_RenderText_Solid(menuFont, menuEntry.c_str(), color)};

			if (!surface) {
				BOOST_LOG_TRIVIAL(fatal) << format("Cannot create surface: {}", TTF_GetError());
				return 1;
			}

			sdl2::TexturePtr texture{ SDL_CreateTextureFromSurface(r, surface.get()) };

			SDL_Rect dest = { 20, i * surface->h + 20, surface->w, surface->h };
			SDL_RenderCopy(r, texture.get(), NULL, &dest);
		}

		SDL_RenderPresent(r);
		///

		SDL_Delay(16);
		gc.clock.atFrameEnd();
	}



	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}
