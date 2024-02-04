#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"

namespace Player {
	extern int playerX;
	extern int playerY;
	extern const int playerSpeed;

	extern bool moveUp;
	extern bool moveDown;
	extern bool moveLeft;
	extern bool moveRight;

	void HandleMovementEvents(SDL_Event event);
	void UpdatePosition();
	void RenderPlayer(SDL_Renderer* renderer, int playerX, int playerY, int playerSpeed);
}

#endif // PLAYER_H
