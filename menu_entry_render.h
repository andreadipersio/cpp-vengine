#pragma once

#include <SDL2/sdl.h>

#include "menu.h"
#include "menu_widget_render.h"
#include "sdl.h"

using sdl2::Render_offset;
using sdl2::Render_context;
using sdl2::Surface_ptr;
using sdl2::Texture_ptr;

class Menu_entry_render {
public:
	Menu_entry_render(menu::Menu_entry&);

	void operator()(Render_context&, Render_offset&);

private:
	menu::Menu_entry& menu_entry_;

	SDL_Color text_color();
};