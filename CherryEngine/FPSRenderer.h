#ifndef FPS_RENDERER_H
#define FPS_RENDERER_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "iostream"

namespace FPSRenderer {
	void Init(TTF_Font* font);
	void RenderFPS(SDL_Renderer* renderer);
	void CleanUp();
} // namespace FPSRenderer

#endif // FPS_RENDERER_H
