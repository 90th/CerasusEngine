#include "Game.h"
#include "FPSRenderer.h"
#include "Player.h"
#include "Logger.h"
#include <vector>
#include <string>
#include <iostream>

namespace Game {
	bool isRunning = true;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* font = nullptr; // Font for rendering text

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
		FPSRenderer::Init(font);
		Logger::logWithLabel("Game", "Game initialized.");
	}

	void CleanUp() {
		Logger::logWithLabel("Game", "Cleaning up FPS renderer...");
		FPSRenderer::CleanUp(); // Clean up FPS rendering
		Logger::logWithLabel("Game", "Closing font...");
		TTF_CloseFont(font);
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
		// Update game state here
		Player::UpdatePosition(); // Update player position
	}

	void Render() {
		SDL_SetRenderDrawColor(renderer, 22, 0, 0, 255);
		SDL_RenderClear(renderer);

		Player::RenderPlayer(renderer, Player::playerX, Player::playerY, Player::playerSpeed);
		FPSRenderer::RenderFPS(renderer);

		SDL_RenderPresent(renderer);
	}

	void Run() {
		Init();

		while (isRunning) {
			Uint32 startTime = SDL_GetTicks(); // Start time of the frame
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