#include "Player.h"

namespace Player {
	int playerX = 100;
	int playerY = 100;
	const int playerSpeed = 5;

	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	SDL_Renderer* renderer = nullptr;

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

	void RenderPlayer(SDL_Renderer* renderer, int playerX, int playerY, int playerSpeed) {
		/**
		* @param renderer: The SDL renderer to draw on
		* @param playerX: The x-coordinate of the player's circle
		* @param playerY: The y-coordinate of the player's circle
		* @param playerSpeed: The speed of the player's circle
		*/
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, playerX, playerY, playerX + 20, playerY); // Base
		SDL_RenderDrawLine(renderer, playerX, playerY, playerX + 10, playerY - 20); // Left side
		SDL_RenderDrawLine(renderer, playerX + 20, playerY, playerX + 10, playerY - 20); // Right side
	}

	void UpdatePosition() {
		if (moveUp)
			playerY -= playerSpeed;
		if (moveDown)
			playerY += playerSpeed;
		if (moveLeft)
			playerX -= playerSpeed;
		if (moveRight)
			playerX += playerSpeed;
	}
}