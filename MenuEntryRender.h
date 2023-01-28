#include <SDL2/SDL.h>

#include "Menu.h"
#include "MenuWidgetRender.h"
#include "SDL.h"

using sdl2::Render_offset;
using sdl2::Rendering_context;
using sdl2::Surface_ptr;
using sdl2::Texture_ptr;

class Menu_entry_render {
public:
	Menu_entry_render(Menu_entry&);

	void render(Rendering_context&, Render_offset&);

private:
	Menu_entry& menu_entry_;

	SDL_Color text_color();
};