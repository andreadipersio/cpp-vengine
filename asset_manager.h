#pragma once

#include "sdl.h"

class Asset_manager {
public:
  Asset_manager(size_t max_size);
  void set_surface(size_t index, SDL_Surface*);
  SDL_Surface* get_surface(size_t index);
  SDL_Surface* get_or_create_surface(size_t index, std::function<SDL_Surface* ()> fn);

private:
  std::vector<SDL_Surface*> surfaces_;
};
