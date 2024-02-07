#include "DebugRenderer.h"
#include <unordered_map>

namespace DebugRenderer {
	// Variables for FPS rendering
	Uint32 prevTime = 0;
	int frameCount = 0;
	float fps = 0.0f;
	TTF_Font* font = nullptr;

	// Map to store debug messages by title
	std::unordered_map<std::string, DebugMessage> debugMessages;

	// Initialize the renderer with the provided font
	void Init(TTF_Font* fontPtr) {
		font = fontPtr;
	}

	void ToggleDebugMenu() {
	}

	void AddDebugMessage(const std::string& title, const std::string& content) {
		debugMessages[title] = { title, content };
	}

	void RemoveDebugMessage(const std::string& title) {
		debugMessages.erase(title);
	}

	void UpdateDebugMessage(const std::string& title, const std::string& content) {
		debugMessages[title].content = content;
	}

	void Render(SDL_Renderer* renderer) {
		// Render FPS
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

		// Render debug messages
		int yPosition = 60; // Starting position for debug messages
		SDL_Color textColor = { 255, 255, 255 }; // White color
		for (const auto& pair : debugMessages) {
			const DebugMessage& msg = pair.second;
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, (msg.title + ": " + msg.content).c_str(), textColor);
			if (textSurface != nullptr) {
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
				if (textTexture != nullptr) {
					SDL_Rect dstRect = { 5, yPosition, textSurface->w, textSurface->h };
					SDL_RenderCopy(renderer, textTexture, nullptr, &dstRect);
					SDL_DestroyTexture(textTexture);
				}
				SDL_FreeSurface(textSurface);
			}
			yPosition += 20; // Increase the y position for the next debug message
		}
	}

	// Clean up resources
	void CleanUp() {
		font = nullptr;
	}
}