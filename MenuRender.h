#include "Menu.h"
#include "MenuEntryRender.h"
#include "SDL.h"

using sdl2::Render_context;
using sdl2::Render_offset;

class Menu_render {
public:
	Menu_render(Menu_manager&);
	
	void operator()(Render_context&, Render_offset&);
private:
	Menu_manager& menu_manager_;
};
