#include "game_settings.h"

void Game_settings::set_resolution(uint16_t width, uint16_t height) {
	resolution_width = width;
	resolution_height = height;
	dirty = true;
}

