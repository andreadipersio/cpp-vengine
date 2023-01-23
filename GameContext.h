#pragma once

#include <map>
#include <SDL2/SDL.h>

#include "Menu.h"
#include "GameClock.h"

struct Game_context {
	std::map<int32_t, SDL_GameController*> controllers;
	Game_clock clock;
	bool running;
	Menu_manager& menu_manager;

	Game_context()
		: running(true), menu_manager(*new Menu_manager) {};
};


