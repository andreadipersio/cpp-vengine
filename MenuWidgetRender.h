#include <variant>
#include <SDL2/SDL.h>

#include "MenuWidget.h"
#include "SDL.h"

using sdl2::Render_offset;
using sdl2::Rendering_context;
using sdl2::Surface_ptr;
using sdl2::Texture_ptr;

class Menu_widget_choice_render {
public:
	Menu_widget_choice_render(Menu_widget_choice&);

	void operator()(Rendering_context&, Render_offset);
private:
	Menu_widget_choice& widget_;
};
