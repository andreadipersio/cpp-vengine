#include <format>
#include <map>
#include <iostream>
#include <boost/log/trivial.hpp>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "GameClock.cpp"
#include "Input.cpp"
#include "SDLControllerEventAdapter.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) {
    BOOST_LOG_TRIVIAL(fatal) << format("SDL_Init Error: {}", SDL_GetError());
  }

  GameClock gameClock;

  SDL_Window* win = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED, 800, 600, 0);


  map<int32_t, SDL_GameController*> controllers;

  input::ActionSet* actionSet = new input::MenuActionSet;

  bool run = true; 

  while (run) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        run = false;
        break;
      case SDL_CONTROLLERDEVICEADDED: {
        auto controllerId = event.cdevice.which;
        BOOST_LOG_TRIVIAL(info) << format(
            "Controller with id '{}' has been detected", controllerId);
        SDL_GameControllerOpen(controllerId);
        auto controller = SDL_GameControllerFromInstanceID(controllerId);
        if (controller) {
          controllers[(int32_t)controllerId] = controller;
        } else {
          BOOST_LOG_TRIVIAL(warning)
              << format("Controller with id '{}' could not be opened: {}",
                        controllerId, SDL_GetError());
        }
        break;
      } 
      case SDL_CONTROLLERBUTTONDOWN:
        if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
          switch (actionSet->id()) {
          case input::GAME_ACTION_SET:
            BOOST_LOG_TRIVIAL(debug) << "Activating MenuActionSet";
            actionSet = new input::MenuActionSet;
            break;
          case input::MENU_ACTION_SET:
            BOOST_LOG_TRIVIAL(debug) << "Activating GameActionSet";
            actionSet = new input::GameActionSet;
            break;
          }
        } else {
          event::ControllerButtonEvent controllerButtonEvent =
              adapter::sdl::controllerEvent::getControllerButtonEvent(&event);
          actionSet->handleInput(&controllerButtonEvent);
        }
        break;
      case SDL_KEYDOWN:
        SDL_Event quitEvent = {SDL_QUIT};
        BOOST_LOG_TRIVIAL(debug) << format("FPS: {}", gameClock.fps);

        switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
          SDL_PushEvent(&quitEvent);
        }
        break;
      }
    }

    gameClock.atFrameStart();
    SDL_Delay(16);
    gameClock.atFrameEnd();
  }

  

  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}
