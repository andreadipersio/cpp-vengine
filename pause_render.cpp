#include "sdl.h"

using sdl::Render_context;

class Pause_render {
public:
	Pause_render() {};
	
	void operator()(Render_context& sdl_ctx) {
			auto font = sdl_ctx.fonts[sdl::MENU_MEDIUM_FONT].get();
			SDL_Color color = { 255, 255, 255 };
			sdl::Surface_ptr surface{ TTF_RenderText_Solid(font, "PAUSED", color) };
			sdl::Texture_ptr texture{ SDL_CreateTextureFromSurface(sdl_ctx.r.get(), surface.get()) };

			int w, h;
			SDL_GetRendererOutputSize(sdl_ctx.r.get(), &w, &h);

			SDL_Rect renderQuad = { 0, 0, surface->w, surface->h };
			renderQuad.x = (w - renderQuad.w) / 2;
			renderQuad.y = (h - renderQuad.h) / 2;

			SDL_RenderCopy(sdl_ctx.r.get(), texture.get(), NULL, &renderQuad);
	};
};
