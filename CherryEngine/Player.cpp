#include "Player.h"

namespace Player {
	int circleX = 100;
	int circleY = 100;
	const int circleSpeed = 5;

	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;

	void HandleMovementEvents(SDL_Event event) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_w:
				moveUp = true;
				break;
			case SDLK_a:
				moveLeft = true;
				break;
			case SDLK_s:
				moveDown = true;
				break;
			case SDLK_d:
				moveRight = true;
				break;
				// Handle other key presses
			}
			break;
		case SDL_KEYUP:
			// Clear flags for released keys
			switch (event.key.keysym.sym) {
			case SDLK_w:
				moveUp = false;
				break;
			case SDLK_a:
				moveLeft = false;
				break;
			case SDLK_s:
				moveDown = false;
				break;
			case SDLK_d:
				moveRight = false;
				break;
				// Handle other key releases
			}
			break;
			// Handle other event types if needed
		}
	}

	void UpdatePosition() {
		if (moveUp)
			circleY -= circleSpeed;
		if (moveDown)
			circleY += circleSpeed;
		if (moveLeft)
			circleX -= circleSpeed;
		if (moveRight)
			circleX += circleSpeed;
	}
}