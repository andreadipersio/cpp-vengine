#include <array>
#include <iostream>
#include <utility>

#include <fmt/core.h>
#include <boost/log/trivial.hpp>
#include <variant>

#define SDL_MAIN_HANDLED

#include "GameContext.h"
#include "GameState.h"

#include "MenuEntryRender.h"

#include "SDL.h"

using fmt::format;

int main(int argc, char* argv[]) {
	Game_context gc{};

	Game_state_machine gameStateMachine{ gc };
	gameStateMachine.initiate();

	sdl2::Rendering_context sdl_ctx = sdl2::make_context_or_throw(gc.settings.resolution_width,
																																gc.settings.resolution_height);

	while (gc.running) {
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

		SDL_SetRenderDrawColor(sdl_ctx.r.get(), 0, 0, 0, 0);
		SDL_RenderClear(sdl_ctx.r.get());

		uint16_t menu_x_top_margin = 20;
		uint16_t menu_y_top_margin = 20;
		sdl2::Render_offset offset{ menu_x_top_margin, menu_y_top_margin };

		for (auto& menuEntry : gc.menu_manager) {
			Menu_entry_render menu_entry_render{ menuEntry };
			menu_entry_render(sdl_ctx, offset);
		}

		SDL_RenderPresent(sdl_ctx.r.get());
		///

		SDL_Delay(16);
		gc.clock.at_frame_end();
	}

	SDL_Quit();

	return 0;
}
