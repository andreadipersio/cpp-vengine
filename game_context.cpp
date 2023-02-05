#include "game_context.h"

Game_context::Game_context()
	: running(true), menu_manager(*new menu::Menu_manager) {};
