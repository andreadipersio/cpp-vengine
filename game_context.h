#pragma once

#include <map>
#include <SDL2/sdl.h>

#include "menu/menu.h"
#include "game_clock.h"
#include "game_settings.h"

struct Game_context {
	std::map<int32_t, SDL_GameController*> controllers;
	Game_clock clock;
	Game_settings settings;
	bool running;
	menu::Menu_manager& menu_manager;

	Game_context();
};
