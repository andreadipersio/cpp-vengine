#pragma once

#include <map>
#include <SDL2/sdl.h>

#include "menu/menu.h"
#include "game_clock.h"
#include "game_settings.h"

enum class Game_state {
	INTRO,
	MENU,
	PLAY,
	PAUSE,
	QUIT
};

struct Game_context {
	std::map<int32_t, SDL_GameController*> controllers;
	Game_clock clock;
	Game_settings settings;
	Game_state state;
	menu::Menu_manager& menu_manager;

	Game_context();
};
