#include "game_context.h"

void Game_settings::set_resolution(uint16_t width, uint16_t height) {
	resolution_width = width;
	resolution_height = height;
	dirty = true;
}

Game_context::Game_context()
	: running(true), menu_manager(*new menu::Menu_manager) {};
