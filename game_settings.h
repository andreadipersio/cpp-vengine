#pragma once

#include <cstdint>

enum class Language_id {
	DEUTSCH,
	ENGLISH,
	ITALIANO
};

struct Game_settings {
	uint16_t resolution_width = 1024;
	uint16_t resolution_height = 768;
	bool dirty = false;

	void set_resolution(uint16_t w, uint16_t h);
};
