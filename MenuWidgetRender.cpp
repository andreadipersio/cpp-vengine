#include "MenuWidgetRender.h"

Menu_widget_choice_render::Menu_widget_choice_render(Menu_widget_choice& widget)
	: widget_(widget) {};

void Menu_widget_choice_render::operator()(Rendering_context& sdl_ctx, Render_offset offset) {
		auto current_choice = widget_.current_choice();
		auto font = sdl_ctx.fonts[sdl2::MENU_MEDIUM_FONT].get();
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

		text_blocks.push_back({ current_choice, active_color });

		{
			SDL_Color color;

			if (widget_.is_last())
				color = inactive_color;
			else
				color = active_color;

			text_blocks.push_back({ ">", color });
		}

		for (auto [text, color] : text_blocks) {
				Surface_ptr surface { TTF_RenderText_Solid(font, text.c_str(), color) };
				Texture_ptr texture{ SDL_CreateTextureFromSurface(sdl_ctx.r.get(), surface.get()) };

				SDL_Rect dest = {
					offset.x,
					offset.y,
					surface->w,
					surface->h
				};

				SDL_RenderCopy(sdl_ctx.r.get(), texture.get(), NULL, &dest);

				offset.x += surface->w + 10;
		}
}
