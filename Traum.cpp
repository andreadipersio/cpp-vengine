#include <array>
#include <iostream>
#include <utility>

#include <fmt/core.h>
#include <boost/log/trivial.hpp>

#define SDL_MAIN_HANDLED

#include "GameContext.h"
#include "GameState.h"

#include "SDL.h"

using fmt::format;

int main(int argc, char* argv[]) {
	Game_context gc{};

	Game_state_machine gameStateMachine{ gc };
	gameStateMachine.initiate();

	sdl2::SDL_context sdl_ctx = sdl2::make_context_or_throw(800, 600);

	while (gc.running) {
		SDL_Event sdlEvent;

		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
			case SDL_QUIT:
				gameStateMachine.process_event(Event_quit_game());
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
					gameStateMachine.process_event(Input_event_start_button{});
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
					gameStateMachine.process_event(Input_event_dpad_down{});
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_UP:
					gameStateMachine.process_event(Input_event_dpad_up{});
					break;
				case SDL_CONTROLLER_BUTTON_A:
					gameStateMachine.process_event(Input_event_button_a{});
					break;
				case SDL_CONTROLLER_BUTTON_B:
					gameStateMachine.process_event(Input_event_button_b{});
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

		gc.clock.at_frame_start();


		SDL_SetRenderDrawColor(sdl_ctx.r.get(), 0, 0, 0, 0);
		SDL_RenderClear(sdl_ctx.r.get());

		///
		auto i = 0;
		for (auto& menuEntry: gc.menu_manager) {
			SDL_Color color;

			if (menuEntry.is_selected) {
				color = { 238, 75, 43 };
			} else {
				color = { 255, 255, 255 };
			}

			auto font = sdl_ctx.fonts[sdl2::MENU_BIG_FONT].get();

			sdl2::Surface_ptr surface{TTF_RenderText_Solid(font, menuEntry.id.c_str(), color)};

			if (!surface) {
				BOOST_LOG_TRIVIAL(fatal) << format("Cannot create surface: {}", TTF_GetError());
				return 1;
			}

			sdl2::Texture_ptr texture{ SDL_CreateTextureFromSurface(sdl_ctx.r.get(), surface.get())};

			SDL_Rect dest = { 20, i * surface->h + 20, surface->w, surface->h };
			SDL_RenderCopy(sdl_ctx.r.get(), texture.get(), NULL, &dest);

			i++;
		}

		SDL_RenderPresent(sdl_ctx.r.get());
		///

		SDL_Delay(16);
		gc.clock.at_frame_end();
	}

	SDL_Quit();

	return 0;
}
