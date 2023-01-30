#pragma once

#include <SDL2/sdl.h>

#include "menu/menu.h"
#include "menu_widget_render.h"
#include "sdl.h"

using sdl::Render_offset;
using sdl::Render_context;
using sdl::Surface_ptr;
using sdl::Texture_ptr;

class Menu_entry_render {
public:
	Menu_entry_render(menu::Menu_entry&);

	void operator()(Render_context&, Render_offset&);

private:
	menu::Menu_entry& menu_entry_;

	SDL_Color text_color();
};