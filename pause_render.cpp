#include "asset_manager.h"
#include "sdl.h"

using sdl::Render_context;

enum class Pause_surfaces: size_t {
	PAUSED
};

class Pause_render {
public:
	Pause_render(): asset_manager_(10) {};
	
	void operator()(Render_context& sdl_ctx) {
			auto font = sdl_ctx.fonts[sdl::MENU_MEDIUM_FONT].get();
			SDL_Color color = { 255, 255, 255 };

			auto create_surface_fn = [font, color]() { 
				BOOST_LOG_TRIVIAL(debug) << "create surface";
				return TTF_RenderText_Solid(font, "PAUSED", color); 
			};
			auto surface = asset_manager_.get_or_create_surface(size_t(Pause_surfaces::PAUSED), create_surface_fn);

			sdl::Texture_ptr texture{ SDL_CreateTextureFromSurface(sdl_ctx.r.get(), surface) };

			int w, h;
			SDL_GetRendererOutputSize(sdl_ctx.r.get(), &w, &h);

			SDL_Rect renderQuad = { 0, 0, surface->w, surface->h };
			renderQuad.x = (w - renderQuad.w) / 2;
			renderQuad.y = (h - renderQuad.h) / 2;

			SDL_RenderCopy(sdl_ctx.r.get(), texture.get(), NULL, &renderQuad);
	};
private:
	Asset_manager asset_manager_;
};
