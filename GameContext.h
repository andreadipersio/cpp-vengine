#pragma once

#include <map>
#include <SDL2/SDL.h>

#include "Menu.h"
#include "GameClock.h"

struct Game_settings {
	uint16_t resolution_width = 1024;
	uint16_t resolution_height = 768;
	bool dirty;

	void set_resolution(uint16_t w, uint16_t h);
};

struct Game_context {
	std::map<int32_t, SDL_GameController*> controllers;
	Game_clock clock;
	Game_settings settings;
	bool running;
	Menu_manager& menu_manager;

	Game_context();
};
