#pragma once

#include <array>
#include <memory>
#include <stdexcept>

#include <boost/log/trivial.hpp>
#include <fmt/core.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

using fmt::format;

// Credits:
// https://swarminglogic.com/scribble/2015_05_smartwrappers
namespace sdl {

enum Font {
	MENU_BIG_FONT,
	MENU_MEDIUM_FONT
};

constexpr uint8_t FONTS_COUNT = 2;

struct SDL_deleter {
	void operator()(SDL_Window* ptr);
	void operator()(SDL_Renderer* ptr);
	void operator()(SDL_Surface* ptr);
	void operator()(SDL_Texture* ptr);
	void operator()(TTF_Font* ptr);
};

using Window_ptr = std::unique_ptr<SDL_Window, SDL_deleter>;
using Renderer_ptr = std::unique_ptr<SDL_Renderer, SDL_deleter>;
using Surface_ptr = std::unique_ptr<SDL_Surface, SDL_deleter>;
using Texture_ptr = std::unique_ptr<SDL_Texture, SDL_deleter>;
using Font_ptr = std::unique_ptr<TTF_Font, SDL_deleter>;

struct Render_context {
	Window_ptr win;
	Renderer_ptr r;

	std::array<Font_ptr, FONTS_COUNT> fonts;

	void apply_config_change(uint16_t, uint16_t);
};

Render_context make_context_or_throw(uint16_t width, uint16_t height);

struct Render_offset {
	uint64_t x;
	uint64_t y;
};
}



