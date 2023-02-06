#include "menu_widget_render.h"

Menu_widget_choice_render::Menu_widget_choice_render(menu::Choice_widget& widget)
	: widget_(widget) {};

void Menu_widget_choice_render::operator()(Render_context& sdl_ctx, Render_offset offset) {
	auto current_choice = widget_.current_choice();
	auto font = sdl_ctx.fonts[sdl::MENU_MEDIUM_FONT].get();
	SDL_Color active_color = { 255, 255, 255 };
	SDL_Color inactive_color = { 127, 133, 135 };

	std::vector<std::tuple<string, SDL_Color>> text_blocks;

	{
		SDL_Color color;

		if (widget_.is_first())
			color = inactive_color;
		else
			color = active_color;

		text_blocks.push_back({ "<", color });
	}

	text_blocks.push_back({ current_choice->label(), active_color });

	{
		SDL_Color color;

		if (widget_.is_last())
			color = inactive_color;
		else
			color = active_color;

		text_blocks.push_back({ ">", color });
	}

	uint16_t width = 0;
	uint16_t height = 0;

	std::vector<Surface_ptr> surfaces;

	for (auto [text, color] : text_blocks) {
		Surface_ptr surface{ TTF_RenderText_Solid(font, text.c_str(), color) };

		width += surface->w + 10;

		if (surface->h > height) {
			height = surface->h;
		}

		surfaces.emplace_back(std::move(surface));
	}

	Surface_ptr surface{ SDL_CreateRGBSurface(0, width, height, 16, 0, 0, 0, 0) };

	uint16_t offset_x = 0;

	for (auto& s : surfaces) {
		SDL_Rect dst = { offset_x, 0, s->w, s->h };
		SDL_BlitSurface(s.get(), NULL, surface.get(), &dst);
		offset_x += s->w + 10;
	}

	SDL_Rect dest = {
		offset.x,
		offset.y,
		surface->w,
		surface->h
	};

	Texture_ptr texture{ SDL_CreateTextureFromSurface(sdl_ctx.r.get(), surface.get()) };
	SDL_RenderCopy(sdl_ctx.r.get(), texture.get(), NULL, &dest);
}
