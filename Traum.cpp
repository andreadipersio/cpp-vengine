#include <iostream>
#include <format>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "GameClock.cpp"

using namespace std;

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
		cout << format("SDL_Init Error: {}", SDL_GetError()) << std::endl;
	}

	GameClock gameClock;

	SDL_Window* win = SDL_CreateWindow(
		"Game Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800, 600, 0);

	bool run = true;

	while (run) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: 
				run = false;
				break;
			case SDL_KEYDOWN:
				SDL_Event quitEvent = { SDL_QUIT };
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
