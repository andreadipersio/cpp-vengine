#include <array>
#include <iostream>
#include <utility>

#include <fmt/core.h>
#include <boost/log/trivial.hpp>
#include <variant>

#define SDL_MAIN_HANDLED

#include "game_context.h"
#include "state_machine/game_state.h"

#include "menu_render.h"

#include "sdl.h"

#include <SDL2/SDL_image.h>

using fmt::format;

int main(int argc, char* argv[]) {
	Game_context gc{};

	state_machine::Game_state_machine gameStateMachine{ gc };
	gameStateMachine.initiate();

	sdl::Render_context sdl_ctx;

	try {
		sdl_ctx = sdl::make_context_or_throw(gc.settings.resolution_width, gc.settings.resolution_height);
	} catch (std::exception& ex) {
		BOOST_LOG_TRIVIAL(fatal) << ex.what();
		return 1;
	}

	while (gc.state != Game_state::QUIT) {
		if (gc.settings.dirty) {
			sdl_ctx.apply_config_change(gc.settings.resolution_width,
																	gc.settings.resolution_height);
			gc.settings.dirty = false;
		}

		SDL_Event sdlEvent;

		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
			case SDL_QUIT:
				gameStateMachine.process_event(Game_event_quit());
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
				case SDL_CONTROLLER_BUTTON_DPAD_UP:
					gameStateMachine.process_event(Input_event_dpad_up{});
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
					gameStateMachine.process_event(Input_event_dpad_left{});
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
					gameStateMachine.process_event(Input_event_dpad_down{});
					break;
				case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
					gameStateMachine.process_event(Input_event_dpad_right{});
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

		//
		// Rendering
		//

		SDL_SetRenderDrawColor(sdl_ctx.r.get(), 0, 0, 0, 0);
		SDL_RenderClear(sdl_ctx.r.get());

		switch (gc.state) {
		case Game_state::MENU:
			Menu_render menu_render{ gc.menu_manager };
			menu_render(sdl_ctx);
			break;
		}

		SDL_RenderPresent(sdl_ctx.r.get());

		// End Rendering

		SDL_Delay(16);
		gc.clock.at_frame_end();
	}

	SDL_Quit();

	return 0;
}
