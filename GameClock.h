#pragma once

#include <chrono>

using namespace std::chrono;

class GameClock {
public:
  const unsigned short int& fps;

  GameClock();
  void atFrameStart();
  void atFrameEnd();

private:
  time_point<steady_clock> frameStart_, frameEnd_;
  nanoseconds frameDelta_;
  unsigned short int fps_;

  nanoseconds CalculateFrameDelta();
  unsigned short int CalculateFps();
};
