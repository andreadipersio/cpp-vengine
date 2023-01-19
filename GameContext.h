#pragma once

#include <map>
#include <SDL2/SDL.h>

#include "Menu.h"
#include "GameClock.h"

struct GameContext {
	std::map<int32_t, SDL_GameController*> controllers;
	GameClock clock;
	bool running;
	Menu& menu;

	GameContext()
		: running(true), menu(*new Menu) {};
};


