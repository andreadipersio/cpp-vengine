#pragma once

#include <chrono>

#include "GameClock.h"

using namespace std::chrono;

GameClock::GameClock() : frameDelta_(0), fps(fps_), fps_(0) {}

void GameClock::atFrameStart() { frameStart_ = steady_clock::now(); }

void GameClock::atFrameEnd() {
  frameEnd_ = steady_clock::now();
  frameDelta_ = CalculateFrameDelta();
  fps_ = CalculateFps();
}

nanoseconds GameClock::CalculateFrameDelta() const { return frameEnd_ - frameStart_; }

unsigned short int GameClock::CalculateFps() const {
  if (frameDelta_ > 0ns) {
    return (unsigned short int)(1s / frameDelta_);
  } else {
    return 0;
  }
}
