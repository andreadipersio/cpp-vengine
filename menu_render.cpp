#include "menu_render.h"

Menu_render::Menu_render(Menu_manager& menu_manager)
	: menu_manager_(menu_manager) {}

void Menu_render::operator()(Render_context& sdl_ctx, Render_offset& offset) {
	for (auto& menu_entry : menu_manager_) {
		Menu_entry_render menu_entry_render{ menu_entry };
		menu_entry_render(sdl_ctx, offset);
	}
}
