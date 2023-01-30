#include "menu_entry_render.h"

Menu_entry_render::Menu_entry_render(menu::Menu_entry& menu_entry)
	: menu_entry_(menu_entry) {};

void Menu_entry_render::operator()(Render_context& sdl_ctx, Render_offset& offset) {
	SDL_Color color;

	auto font = sdl_ctx.fonts[sdl2::MENU_BIG_FONT].get();

	Surface_ptr surface{ TTF_RenderText_Solid(font, menu_entry_.id.c_str(), text_color()) };
	Texture_ptr texture{ SDL_CreateTextureFromSurface(sdl_ctx.r.get(), surface.get()) };

	SDL_Rect dest = { offset.x, offset.y, surface->w, surface->h };
	SDL_RenderCopy(sdl_ctx.r.get(), texture.get(), NULL, &dest);

	if (auto widget = menu_entry_.widget) {
		sdl2::Render_offset widget_offset = { surface->w + 50, dest.y + 5 };
		std::visit([&sdl_ctx, widget_offset](Menu_widget_choice* widget) {
			Menu_widget_choice_render widget_renderer{ *widget };
		widget_renderer(sdl_ctx, widget_offset);
		}, widget.value());
	}

	offset.y += surface->h + 5;
}

SDL_Color Menu_entry_render::text_color() {
	if (menu_entry_.is_selected) {
		return { 99, 155, 255 };
	} else {
		return{ 255, 255, 255 };
	}
}
