#include "Player.h"

namespace Player {
	int playerX = 100;
	int playerY = 100;
	const int playerSpeed = 5;

	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;

	// Animation constants and variables
	const int NUM_FRAMES = 3; // Number of frames in each animation
	const int IDLE_FRAME_SEQUENCE[NUM_FRAMES] = { 0, 1, 2 }; // Sequence of frames for idle animation
	const int LEFT_FRAME_SEQUENCE[NUM_FRAMES] = { 9, 10, 11 }; // Sequence of frames for left animation
	const int RIGHT_FRAME_SEQUENCE[NUM_FRAMES] = { 3, 4, 5 }; // Sequence of frames for right animation
	const int DOWN_FRAME_SEQUENCE[NUM_FRAMES] = { 6, 7, 8 }; // Sequence of frames for down animation

	// Define a constant for the animation delay (in milliseconds)
	const Uint32 ANIMATION_DELAY = 100; // Adjust this value to control the animation speed

	// Define a variable to keep track of the last time the animation was updated
	Uint32 lastUpdateTime = 0;

	int currentFrameIndex = 0; // Index of the current frame in the animation sequence

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
			playerY -= playerSpeed;
		if (moveDown)
			playerY += playerSpeed;
		if (moveLeft)
			playerX -= playerSpeed;
		if (moveRight)
			playerX += playerSpeed;
	}

	void UpdateAnimation() {
		// Get the current time
		Uint32 currentTime = SDL_GetTicks();

		// Check if enough time has passed since the last animation update
		if (currentTime - lastUpdateTime >= ANIMATION_DELAY) {
			// Update the animation frame index only if enough time has passed
			if (moveUp || moveDown || moveLeft || moveRight)
				currentFrameIndex = (currentFrameIndex + 1) % NUM_FRAMES;
			else
				currentFrameIndex = 0; // Reset to idle frame if not moving

			// Update the last update time to the current time
			lastUpdateTime = currentTime;
		}
	}

	void RenderPlayer(SDL_Renderer* renderer, SDL_Texture* playerTexture, int frameWidth, int frameHeight) {
		// Update player position based on movement
		UpdatePosition();
		// Update player animation
		UpdateAnimation();

		const int* frameSequence;
		if (moveUp)
			frameSequence = IDLE_FRAME_SEQUENCE;
		else if (moveDown)
			frameSequence = DOWN_FRAME_SEQUENCE;
		else if (moveLeft)
			frameSequence = LEFT_FRAME_SEQUENCE;
		else if (moveRight)
			frameSequence = RIGHT_FRAME_SEQUENCE;
		else
			frameSequence = IDLE_FRAME_SEQUENCE; // Default to idle

		// Adjust source rectangle to skip empty frames
		int frameIndex = frameSequence[currentFrameIndex];
		int frameX = frameIndex % 3;  // Assuming 3 frames per row
		int frameY = frameIndex / 3;  // Assuming 3 frames per column
		SDL_Rect srcRect = { frameX * frameWidth, frameY * frameHeight, frameWidth, frameHeight };

		// Destination rectangle for rendering
		SDL_Rect destRect = { playerX, playerY, frameWidth, frameHeight };

		// Render the current frame of the player sprite
		SDL_RenderCopy(renderer, playerTexture, &srcRect, &destRect);
	}
}