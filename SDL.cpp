#include "SDL.h"

namespace sdl {

void SDL_deleter::operator()(SDL_Window* ptr) {
	if (ptr) SDL_DestroyWindow(ptr);
}

void SDL_deleter::operator()(SDL_Renderer* ptr) {
	if (ptr) SDL_DestroyRenderer(ptr);
}

void SDL_deleter::operator()(SDL_Surface* ptr) {
	if (ptr) SDL_FreeSurface(ptr);
}

void SDL_deleter::operator()(SDL_Texture* ptr) {
	if (ptr) SDL_DestroyTexture(ptr);
}

void SDL_deleter::operator()(TTF_Font* ptr) {
	if (ptr) TTF_CloseFont(ptr);
}

void Render_context::apply_config_change(uint16_t width, uint16_t height) {
	r.reset();
	win.reset();

	Window_ptr new_win{ SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED,
																	 SDL_WINDOWPOS_CENTERED, width, height, 0) };

	if (!new_win) {
		throw std::runtime_error{format("SDL_CreateWindow Error: {}", SDL_GetError())};
	}

	Renderer_ptr new_r{ SDL_CreateRenderer(new_win.get(), -1, SDL_RENDERER_ACCELERATED) };

	if (!new_r) {
		throw std::runtime_error{format("SDL_CreateRenderer Error: {}", SDL_GetError())};
	}

	win = std::move(new_win);
	r = std::move(new_r);
}

Render_context make_context_or_throw(uint16_t width, uint16_t height) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) {
		throw std::runtime_error(format("SDL_Init Error: {}", SDL_GetError()));
	}

	if (TTF_Init() != 0) {
		throw std::runtime_error(format("TTF_Init Error: {}", TTF_GetError()));
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		throw std::runtime_error(format("IMG_Init Error: {}", IMG_GetError()));
	}

	Window_ptr win{ SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED,
																		 SDL_WINDOWPOS_CENTERED, width, height, 0) };

	if (!win) {
		throw std::runtime_error{format("SDL_CreateWindow Error: {}", SDL_GetError())};
	}

	Renderer_ptr r{ SDL_CreateRenderer(win.get(), -1, SDL_RENDERER_ACCELERATED) };

	if (!r) {
		throw std::runtime_error(format("SDL_CreateRenderer Error: {}", SDL_GetError()));
	}

	Font_ptr menuFont1{TTF_OpenFont("F:/projects/VEngine/assets/MenuFont.ttf", 24)};
	Font_ptr menuFont2{TTF_OpenFont("F:/projects/VEngine/assets/MenuFont.ttf", 18)};

	if (!menuFont1 || !menuFont2) {
		throw std::runtime_error(format("Cannot load font: {}", TTF_GetError()));
	}

	Render_context context{};
	context.win = std::move(win);
	context.r = std::move(r);
	context.fonts[MENU_BIG_FONT] = std::move(menuFont1);
	context.fonts[MENU_MEDIUM_FONT] = std::move(menuFont2);

	return context;
}
}


