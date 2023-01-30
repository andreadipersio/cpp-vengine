#pragma once

#include <variant>
#include <SDL2/sdl.h>

#include "menu/menu_widget.h"
#include "sdl.h"

using sdl::Render_offset;
using sdl::Render_context;
using sdl::Surface_ptr;
using sdl::Texture_ptr;

class Menu_widget_choice_render {
public:
	Menu_widget_choice_render(menu::Choice_widget&);

	void operator()(Render_context&, Render_offset);
private:
	menu::Choice_widget& widget_;
};
