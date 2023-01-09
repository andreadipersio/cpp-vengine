#pragma once

#include <map>
#include <SDL2/SDL.h>

#include "Input.h"
#include "GameClock.h"

struct GameContext {
  input::ActionSet* actionSet;
  std::map<int32_t, SDL_GameController*> controllers;
  GameClock clock;
};


