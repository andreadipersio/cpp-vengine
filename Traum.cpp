#include <format>
#include <map>
#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "GameClock.cpp"

using namespace std;

int main() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) {
    cout << format("SDL_Init Error: {}", SDL_GetError()) << std::endl;
  }

  GameClock gameClock;

  SDL_Window* win = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED, 800, 600, 0);


  map<int32_t, SDL_GameController*> controllers;

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
        cout << format("Controller with id '{}' has been detected", controllerId) << std::endl;
        SDL_GameControllerOpen(controllerId);
        auto controller = SDL_GameControllerFromInstanceID(controllerId);
        if (controller) {
          controllers[(int32_t)controllerId] = controller;
        } else {
          cout << format("Controller with id '{}' could not be opened: {}",
                         controllerId, SDL_GetError())
               << std::endl;
        }
        break;
      } 
      case SDL_CONTROLLERBUTTONDOWN:
        cout << format("FPS: {}", gameClock.fps) << std::endl;
        break;
      case SDL_KEYDOWN:
        SDL_Event quitEvent = {SDL_QUIT};
        cout << format("FPS: {}", gameClock.fps) << std::endl;

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
