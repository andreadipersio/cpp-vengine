#include "Menu.h"
#include "SDL.h"

using sdl2::Rendering_context;
using sdl2::Render_offset;

class Menu_render {
	Menu_render(Menu_manager&);
	
	void operator()(Rendering_context&, Render_offset&);
private:
	Menu_manager& menu_manager_;
};
