# CMakeList.txt : CMake project for Traum, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)

project ("Traum")

find_package(Boost REQUIRED COMPONENTS chrono log locale)
find_package(Fmt REQUIRED CONFIG)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)



add_executable (Traum 
	"Traum.cpp"  
	"GameClock.cpp" 
	"GameContext.cpp"
	"GameState.cpp" 
	"Menu.cpp"
    "Events.h" 
	"SDL.cpp"
	"MenuWidget.cpp"
    "Events.cpp"
	"MenuState.cpp"
	"MenuSettingsState.cpp"
    "MenuWidgetRender.cpp"
	"MenuEntryRender.cpp"
)

target_link_libraries(Traum PRIVATE 
	SDL2::SDL2 
	$<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
	Boost::log_setup 
	Boost::log 
	Boost::locale
	fmt::fmt
)
