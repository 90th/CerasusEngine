#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_ttf.h"

#include "Player.h"
#include "Logger.h"
#include "Game.h"
#include "DebugRenderer.h"

#include <vector>
#include <string>
#include <iostream>

namespace Game {
	void Init();
	void CleanUp();
	void HandleEvents();
	void Update();
	void Render();
	void Run();
	void LoadPlayerTexture(SDL_Renderer* renderer);
} // namespace Game

#endif // GAME_H
