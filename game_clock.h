#pragma once

#include <chrono>

using namespace std::chrono;

class Game_clock {
public:
	Game_clock();
	void at_frame_start();
	void at_frame_end();
	unsigned short int fps() const;

private:
	time_point<steady_clock> frame_start_, frame_end_;
	nanoseconds frame_delta_;
	unsigned short int fps_;

	nanoseconds calculate_frame_delta() const;
	unsigned short int calculate_fps() const;
};
