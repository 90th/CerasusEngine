#include "Player.h"

namespace Player {
	int playerX = 100;
	int playerY = 100;
	const int playerSpeed = 5;

	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;

	bool shootingEnabled = false;

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

	// Bullets will be moved to its own BulletManager (bullet for now, just a simple POC to figure out what i am doing.)
	struct Bullet {
		double x, y;
		double vx, vy;
		bool active;
		Uint32 shootTime;
	};

	const int MAX_BULLETS = 10;
	std::vector<Bullet> bullets(MAX_BULLETS);
	// define separate vectors for active and inactive bullets
	std::deque<Bullet> activeBullets;
	std::deque<Bullet> inactiveBullets;

	void Shoot() {
		if (activeBullets.size() >= MAX_BULLETS) {
			DebugRenderer::AddDebugMessage("[Shoot]", "Maximum number of active bullets reached. Cannot shoot.");
			return;
		}

		// check if there are inactive bullets available in the pool
		if (!inactiveBullets.empty()) {
			// take an inactive bullet from the pool
			Bullet& bullet = inactiveBullets.front();

			// set bullet properties
			bullet.x = playerX + 29;
			bullet.y = playerY + 25;

			if (moveLeft) {
				bullet.x = playerX + 22;
				bullet.y = playerY + 25;
				bullet.vx = -10;
				bullet.vy = 0;
			}
			else if (moveRight) {
				bullet.x = playerX + 48;
				bullet.y = playerY + 25;
				bullet.vx = 10;
				bullet.vy = 0;
			}
			else {
				bullet.x = playerX + 29;
				bullet.y = playerY + 25;
				bullet.vx = 0;
				bullet.vy = -10;
			}

			// activate the bullet
			bullet.active = true;

			// set the shoot time
			bullet.shootTime = SDL_GetTicks();

			// move the bullet to the active bullets vector
			activeBullets.push_back(std::move(bullet));

			// remove the bullet from the pool of inactive bullets
			inactiveBullets.pop_front();

			// debug messages
			DebugRenderer::AddDebugMessage("[Shoot]", "Bullet shot: x = " + std::to_string(bullet.x) + ", y = " + std::to_string(bullet.y));
		}
	}

	void UpdateBullets() {
		for (auto& bullet : activeBullets) {
			// update bullet position
			bullet.x += bullet.vx;
			bullet.y += bullet.vy;
			// Check if bullet's time is up (10 seconds)
			if (SDL_GetTicks() - bullet.shootTime >= 10000) {
				bullet.active = false;
				inactiveBullets.push_back(std::move(bullet)); // Move bullet back to inactive pool
				DebugRenderer::AddDebugMessage("[UpdateBullets]", "Bullet deactivated due to timeout: x = " + std::to_string(bullet.x) + ", y = " + std::to_string(bullet.y));
			}

			// check if bullet is out of bounds or hit something
			// if it did, deactivate the bullet
			// soon collision detection logic here
			if (bullet.y < 0 || bullet.y > 720 || bullet.x < 0 || bullet.x > 1280) {
				bullet.active = false;
				inactiveBullets.push_back(std::move(bullet)); // Move bullet back to inactive pool
				DebugRenderer::AddDebugMessage("[UpdateBullets]", "Bullet deactivated due to out of bounds: x = " + std::to_string(bullet.x) + ", y = " + std::to_string(bullet.y));
			}
		}

		// remove inactive bullets from active bullets vector
		activeBullets.erase(std::remove_if(activeBullets.begin(), activeBullets.end(),
			[](const Bullet& bullet) { return !bullet.active; }), activeBullets.end());
	}
	void renderBullets(SDL_Renderer* renderer) {
		std::vector<decltype(activeBullets)::iterator> bulletsToRemove;

		for (auto it = activeBullets.begin(); it != activeBullets.end(); ++it) {
			Bullet& bullet = *it;
			if (bullet.active) {
				Uint8 alpha = 255;
				Uint32 elapsedTime = SDL_GetTicks() - bullet.shootTime;
				if (elapsedTime < 1500) {
					alpha = static_cast<Uint8>(255 * (1.0 - static_cast<double>(elapsedTime) / 1500.0));
				}
				else {
					bulletsToRemove.push_back(it);
					continue;
				}

				// Calculate hue based on time
				double hue = static_cast<double>(SDL_GetTicks()) / 10.0; // Adjust this value to control the speed of the color change
				hue = fmod(hue, 360.0); // Wrap around to ensure hue stays within [0, 360)
				// Convert HSV to RGB
				double c = 1.0;
				double x = c * (1 - std::abs(fmod(hue / 60.0, 2.0) - 1));
				double m = 0.0;
				double r, g, b;
				if (hue >= 0 && hue < 60) {
					r = c;
					g = x;
					b = 0;
				}
				else if (hue >= 60 && hue < 120) {
					r = x;
					g = c;
					b = 0;
				}
				else if (hue >= 120 && hue < 180) {
					r = 0;
					g = c;
					b = x;
				}
				else if (hue >= 180 && hue < 240) {
					r = 0;
					g = x;
					b = c;
				}
				else if (hue >= 240 && hue < 300) {
					r = x;
					g = 0;
					b = c;
				}
				else {
					r = c;
					g = 0;
					b = x;
				}

				SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(r * 255), static_cast<Uint8>(g * 255), static_cast<Uint8>(b * 255), alpha);

				SDL_Rect bulletRect = { static_cast<int>(bullet.x), static_cast<int>(bullet.y), 4, 4 };
				SDL_RenderFillRect(renderer, &bulletRect);
			}
		}

		for (auto it : bulletsToRemove) {
			(*it).active = false;
			inactiveBullets.push_back(std::move(*it));
			activeBullets.erase(it);
		}
	}

	void InitializeBullets() {
		// Initialize the pool of bullets
		for (int i = 0; i < MAX_BULLETS; ++i) {
			inactiveBullets.emplace_back(); // Add an inactive bullet to the pool
		}
	}

	void HandleMovementEvents(SDL_Event event) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_w:
				moveUp = true;
				break;
			case SDLK_a:
				moveLeft = true;
				shootingEnabled = false;
				break;
			case SDLK_s:
				moveDown = true;
				break;
			case SDLK_d:
				moveRight = true;
				shootingEnabled = false;
				break;
			case SDLK_SPACE:
				if (shootingEnabled) {
					Shoot();
				}
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
			case SDLK_SPACE:
				shootingEnabled = true; // Enable shooting when space bar is released
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
			// Update the animation frame index
			currentFrameIndex = (currentFrameIndex + 1) % NUM_FRAMES;

			// Update the last update time to the current time
			lastUpdateTime = currentTime;
		}
	}

	void RenderPlayer(SDL_Renderer* renderer, SDL_Texture* playerTexture, int frameWidth, int frameHeight) {
		// Update player position based on movement
		UpdatePosition();

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
		int scaleFactor = 2; // Adjust this value to change the scale factor
		SDL_Rect destRect = { playerX, playerY, frameWidth * scaleFactor, frameHeight * scaleFactor }; // Adjust dimensions here

		// Render the current frame of the player sprite
		SDL_RenderCopy(renderer, playerTexture, &srcRect, &destRect);
	}
}