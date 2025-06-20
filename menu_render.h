#include "menu/menu.h"
#include "menu_entry_render.h"
#include "sdl.h"

using sdl::Render_context;
using sdl::Render_offset;

class Menu_render {
public:
	Menu_render(menu::Menu_manager&);
	
	void operator()(Render_context&);
	void operator()(Render_context&, Render_offset&);
private:
	menu::Menu_manager& menu_manager_;
};
