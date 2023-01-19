# CMakeList.txt : CMake project for Traum, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)

project ("Traum")

find_package(Boost REQUIRED COMPONENTS chrono log locale)
find_package(Fmt REQUIRED CONFIG)
find_package(SDL2 REQUIRED)


add_executable (Traum 
	"Traum.cpp"  
	"GameClock.cpp" 
	"GameContext.h"   
	"GameState.cpp" 
	"Menu.cpp"
)

target_link_libraries(Traum PRIVATE 
	SDL2::SDL2 
	Boost::log_setup 
	Boost::log 
	Boost::locale
	fmt::fmt
)
