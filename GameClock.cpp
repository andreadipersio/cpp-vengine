#pragma once

#include <chrono>

using namespace std::chrono;

class GameClock {
public:
  const unsigned short int& fps;

  GameClock() : frameDelta(0), fps(fps_), fps_(0) {}

  void atFrameStart() { frameStart = steady_clock::now(); }

  void atFrameEnd() {
    frameEnd = steady_clock::now();
    frameDelta = CalculateFrameDelta();
    fps_ = CalculateFps();
  }

private:
  time_point<steady_clock> frameStart, frameEnd;
  nanoseconds frameDelta;

  unsigned short int fps_;

  nanoseconds CalculateFrameDelta() { return frameEnd - frameStart; }

  unsigned short int CalculateFps() {
    if (frameDelta > 0ns) {
      return (unsigned short int)(1s / frameDelta);
    } else {
      return 0;
    }
  }
};
