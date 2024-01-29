#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"

namespace Player {
	extern int circleX;
	extern int circleY;
	extern const int circleSpeed;

	extern bool moveUp;
	extern bool moveDown;
	extern bool moveLeft;
	extern bool moveRight;

	void HandleMovementEvents(SDL_Event event);
	void UpdatePosition();
}

#endif // PLAYER_H
