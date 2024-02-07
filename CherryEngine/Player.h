#ifndef PLAYER_H
#define PLAYER_H

#include "DebugRenderer.h"
#include "SDL.h"
#include "Logger.h"
#include <deque>
#include <vector>

namespace Player {
	extern int playerX;
	extern int playerY;
	extern const int playerSpeed;

	extern bool moveUp;
	extern bool moveDown;
	extern bool moveLeft;
	extern bool moveRight;

	void Shoot();

	void UpdateBullets();

	void renderBullets(SDL_Renderer* renderer);

	void InitializeBullets();

	void HandleMovementEvents(SDL_Event event);
	void UpdatePosition();
	void UpdateAnimation();
	void RenderPlayer(SDL_Renderer* renderer, SDL_Texture* playerTexture, int frameWidth, int frameHeight);
}

#endif // PLAYER_H
