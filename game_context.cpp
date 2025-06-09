#include "game_context.h"

Game_context::Game_context()
	: state(Game_state::INTRO), menu_manager(*new menu::Menu_manager) {};
