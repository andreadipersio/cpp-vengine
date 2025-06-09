#include "menu_render.h"

Menu_render::Menu_render(menu::Menu_manager& menu_manager)
	: menu_manager_(menu_manager) {}

void Menu_render::operator()(Render_context& sdl_ctx) {
		uint16_t menu_x_top_margin = 20;
		uint16_t menu_y_top_margin = 20;
		sdl::Render_offset initial_offset{ menu_x_top_margin, menu_y_top_margin };

		(*this)(sdl_ctx, initial_offset);
}

void Menu_render::operator()(Render_context& sdl_ctx, Render_offset& offset) {
	sdl::Texture_ptr menu_bkg_texture{ IMG_LoadTexture(sdl_ctx.r.get(), "F:/projects/VEngine/assets/MenuBackground.png") };
	SDL_Rect bkg_geometry{ 0, 0, 1024, 768 };

	SDL_RenderCopy(sdl_ctx.r.get(), menu_bkg_texture.get(), NULL, &bkg_geometry);

	for (auto& menu_entry : menu_manager_) {
		Menu_entry_render menu_entry_render{ menu_entry };
		menu_entry_render(sdl_ctx, offset);
	}
}
