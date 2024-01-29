#include "FPSRenderer.h"
#include "Logger.h"
#include <string>

namespace FPSRenderer {
	// Define variables
	Uint32 prevTime = 0;
	int frameCount = 0;
	float fps = 0.0f;
	TTF_Font* font = nullptr;

	void Init(TTF_Font* fontPtr) {
		font = fontPtr;
	}

	void RenderFPS(SDL_Renderer* renderer) {
		Uint32 currentTime = SDL_GetTicks();
		frameCount++;
		if (currentTime - prevTime >= 1000) {
			fps = static_cast<float>(frameCount) / ((currentTime - prevTime) / 1000.0f);
			prevTime = currentTime;
			frameCount = 0;
		}

		// Render FPS text
		if (font != nullptr) {
			SDL_Color textColor = { 255, 255, 255 }; // White color
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, ("FPS: " + std::to_string(static_cast<int>(fps))).c_str(), textColor);
			if (textSurface != nullptr) {
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
				if (textTexture != nullptr) {
					SDL_Rect dstRect = { 5, 5, textSurface->w, textSurface->h };
					SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
					SDL_DestroyTexture(textTexture);
				}
				SDL_FreeSurface(textSurface);
			}
		}
	}

	void CleanUp() {
		font = nullptr;
	}
} // namespace FPSRenderer