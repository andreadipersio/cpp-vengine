#pragma once

#include <chrono>

#include "game_clock.h"

using namespace std::chrono;

Game_clock::Game_clock() : frame_delta_(0), fps_(0) {
}

void Game_clock::at_frame_start() {
	frame_start_ = steady_clock::now();
}

void Game_clock::at_frame_end() {
	frame_end_ = steady_clock::now();
	frame_delta_ = calculate_frame_delta();
	fps_ = calculate_fps();
}

unsigned short int Game_clock::fps() const {
	return fps_;
}

nanoseconds Game_clock::calculate_frame_delta() const {
	return frame_end_ - frame_start_;
}

unsigned short int Game_clock::calculate_fps() const {
	if (frame_delta_ > 0ns) {
		return (unsigned short int)(1s / frame_delta_);
	} else {
		return 0;
	}
}
