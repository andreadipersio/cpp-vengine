#include "SDL.h"

namespace sdl2 {

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

SDL_context make_context_or_throw(uint8_t width, uint8_t height) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) {
		throw std::runtime_error(format("SDL_Init Error: {}", SDL_GetError()));
	}

	if (TTF_Init() != 0) {
		throw std::runtime_error(format("TTF_Init Error: {}", TTF_GetError()));
	}

	Window_ptr win{ SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED,
																		 SDL_WINDOWPOS_CENTERED, 800, 600, 0) };

	if (!win) {
		throw std::runtime_error(format("SDL_CreateWindow Error: {}", SDL_GetError()));
	}

	Renderer_ptr r{ SDL_CreateRenderer(win.get(), -1, SDL_RENDERER_ACCELERATED) };

	if (!r) {
		throw std::runtime_error(format("SDL_CreateRenderer Error: {}", SDL_GetError()));
	}

	SDL_context context{};
	context.win = std::move(win);
	context.r = std::move(r);

	return context;
}
}


