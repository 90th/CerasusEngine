#include "Game.h"
#include "SDL_image.h"

namespace Game {
	bool isRunning = true;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* font = nullptr; // Font for rendering text
	int frameWidth = 32;  // Width of each frame in pixels
	int frameHeight = 32; // Height of each frame in pixels
	// Define player texture globally or in a scope accessible to the rendering function
	SDL_Texture* playerTexture;

	void FontInit() {
		Logger::logWithLabel("Game", "Initializing font...");
		if (TTF_Init() == -1) {
			std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
			Game::isRunning = false;
			return;
		}

		Logger::logWithLabel("Game", "Font initialized.");
		font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 17);

		if (font == nullptr) {
			std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
			isRunning = false;
			return;
		}
		Logger::logWithLabel("Game", "Font loaded.");
	}

	void Init() {
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("[CherryEngine]", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);
		FontInit();
		DebugRenderer::Init(font);

		LoadPlayerTexture(renderer);
		Player::InitializeBullets();
		Logger::logWithLabel("Game", "Game initialized.");
		DebugRenderer::AddDebugMessage("[Game]", "Game Initialized");
	}

	void CleanUp() {
		Logger::logWithLabel("Game", "Cleaning up FPS renderer...");
		DebugRenderer::CleanUp(); // Clean up FPS rendering
		Logger::logWithLabel("Game", "Closing font...");
		DebugRenderer::CleanUp();
		Logger::logWithLabel("Game", "Quitting TTF...");
		TTF_Quit();
		Logger::logWithLabel("Game", "Destroying renderer...");
		SDL_DestroyRenderer(renderer);
		Logger::logWithLabel("Game", "Destroying window...");
		SDL_DestroyWindow(window);
		Logger::logWithLabel("Game", "Quitting SDL...");
		SDL_Quit();
		Logger::logWithLabel("Game", "Game cleaned up.");
	}

	void HandleEvents() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			default:
				Player::HandleMovementEvents(event); // Delegate movement events to Player namespace
				break;
			}
		}
	}

	void Update() {
		Player::UpdateBullets();
		Player::UpdateAnimation();
	}

	void LoadPlayerTexture(SDL_Renderer* renderer) {
		// Load player texture from file
		SDL_Surface* playerSurface = IMG_Load("32x32-bat-sprite.png");
		playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
		SDL_FreeSurface(playerSurface);
	}

	void Render() {
		SDL_SetRenderDrawColor(renderer, 22, 0, 0, 255);
		SDL_RenderClear(renderer);
		DebugRenderer::Render(renderer);

		// Render player with the loaded texture
		Player::RenderPlayer(renderer, playerTexture, frameWidth, frameHeight);
		Player::renderBullets(renderer);

		SDL_RenderPresent(renderer);
	}

	void Run() {
		Logger::logWithLabel("#>", "We are all alone on life's journey, held captive by the limitations of human conciousness");
		Init();

		while (isRunning) {
			Uint32 startTime = SDL_GetTicks(); // Start time of the
			HandleEvents();
			Update();
			Render();
			Uint32 frameTime = SDL_GetTicks() - startTime; // Time taken to process the frame
			if (frameTime < 16) { // Cap frame rate to approximately 60 FPS (1000 ms / 60)
				SDL_Delay(16 - frameTime);
			}
		}

		CleanUp();
	}
} // namespace Game