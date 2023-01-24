#pragma once

#include <array>
#include <memory>
#include <stdexcept>

#include <fmt/core.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using fmt::format;

// Credits:
// https://swarminglogic.com/scribble/2015_05_smartwrappers
namespace sdl2 {

enum Font {
	MENU_FONT
};

constexpr uint8_t FONTS_COUNT = 1;

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

struct SDL_context {
	Window_ptr win;
	Renderer_ptr r;

	std::array<Font_ptr, FONTS_COUNT> fonts;
};

SDL_context make_context_or_throw(uint8_t width, uint8_t height);
}


