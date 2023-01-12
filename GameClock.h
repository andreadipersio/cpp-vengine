#pragma once

#include <chrono>

using namespace std::chrono;

class GameClock {
public:
	GameClock();
	void atFrameStart();
	void atFrameEnd();
	unsigned short int fps() const;

private:
	time_point<steady_clock> frameStart_, frameEnd_;
	nanoseconds frameDelta_;
	unsigned short int fps_;

	nanoseconds CalculateFrameDelta() const;
	unsigned short int CalculateFps() const;
};
