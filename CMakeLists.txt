# CMakeList.txt : CMake project for VEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)

project ("VEngine")

find_package(Boost REQUIRED COMPONENTS chrono log locale)
find_package(Fmt REQUIRED CONFIG)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)



add_executable (VEngine 
	"game.cpp"  
	"game_clock.cpp" 
	"game_context.cpp"
	"game_settings.cpp"
	"state_machine/game_state.cpp" 
	"menu/menu.cpp"
	"menu/menu_widget.cpp"
    "events.cpp" 
	"sdl.cpp"
    "events.cpp"
	"state_machine/menu_state.cpp"
	"state_machine/menu_settings_state.cpp"
    "menu_widget_render.cpp"
	"menu_entry_render.cpp"
	"menu_render.cpp"
)

target_link_libraries(VEngine PRIVATE 
	SDL2::SDL2 
	$<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
	Boost::log_setup 
	Boost::log 
	Boost::locale
	fmt::fmt
)
