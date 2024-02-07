#ifndef DEBUG_RENDERER_H
#define DEBUG_RENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

namespace DebugRenderer {
	struct DebugMessage {
		std::string title;
		std::string content;
	};

	void ToggleDebugMenu();
	void AddDebugMessage(const std::string& title, const std::string& content);
	void RemoveDebugMessage(const std::string& title);
	void UpdateDebugMessage(const std::string& title, const std::string& content);
	void Render(SDL_Renderer* renderer);
	void Init(TTF_Font* font);
	void CleanUp();
}

#endif
