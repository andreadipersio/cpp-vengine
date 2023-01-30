#include "menu.h"
#include "menu_entry_render.h"
#include "sdl.h"

using sdl2::Render_context;
using sdl2::Render_offset;

class Menu_render {
public:
	Menu_render(Menu_manager&);
	
	void operator()(Render_context&, Render_offset&);
private:
	Menu_manager& menu_manager_;
};
