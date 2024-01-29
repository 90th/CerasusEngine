#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_ttf.h"

namespace Game {
	void Init();
	void CleanUp();
	void HandleEvents();
	void Update();
	void Render();
	void Run();
} // namespace Game

#endif // GAME_H
