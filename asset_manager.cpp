#include "asset_manager.h"

Asset_manager::Asset_manager(size_t max_size): surfaces_(max_size, nullptr) {}

void Asset_manager::set_surface(size_t index, SDL_Surface* surface) {
	surfaces_[index] = surface;
}

SDL_Surface* Asset_manager::get_surface(size_t index) {
	return surfaces_[index];
}

SDL_Surface* Asset_manager::get_or_create_surface(size_t index, std::function<SDL_Surface* ()> fn) {
	SDL_Surface* surface = get_surface(index);

	if (surface) {
		BOOST_LOG_TRIVIAL(debug) << "cache hit";
		return surface;
	}

	auto new_surface = fn();

	set_surface(index, new_surface);

	return new_surface;
}


