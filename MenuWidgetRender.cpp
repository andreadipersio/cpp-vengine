#include "MenuWidgetRender.h"

Menu_widget_choice_render::Menu_widget_choice_render(Menu_widget_choice& widget)
	: widget_(widget) {};

void Menu_widget_choice_render::render(Rendering_context& sdl_ctx, Render_offset offset) {
		auto font = sdl_ctx.fonts[sdl2::MENU_MEDIUM_FONT].get();
		SDL_Color color = { 255, 255, 255 };

		{
			Surface_ptr surface { TTF_RenderText_Solid(font, widget_.current_choice().c_str(), color) };
			Texture_ptr texture { SDL_CreateTextureFromSurface(sdl_ctx.r.get(), surface.get()) };

			SDL_Rect dest = { 
				offset.x,
				offset.y,
				surface->w, 
				surface->h 
			};

			SDL_RenderCopy(sdl_ctx.r.get(), texture.get(), NULL, &dest);
		}

}
