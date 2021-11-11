#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

SDL_Texture* tex1;
SDL_Texture* tex2;

Game::Game() {
}
Game::~Game() {
}

void Game::init(const std::string& title, int x, int y, int width, int height, bool fullscreen) {
	
	int flags = 0;
	if (fullscreen) 
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "All subsystems initialized" << std::endl;
		
		window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
		if (window) 
			std::cout << "Window has been created successfully" << std::endl;
		else 
			printError("Couldn't create window!: ");

		Game::renderer = SDL_CreateRenderer(window, -1, 0);
		if (Game::renderer) {
			SDL_SetRenderDrawColor(Game::renderer, 100, 100, 255, 255);
			std::cout << "Renderer has been created successfully" << std::endl;
		}
		else {
			printError("Couldn't create renderer!: ");
		}
		isRunning = true;
	}
	else {
		isRunning = false;
		printError("Couldn't init() everything!: ");
	}

	//Map
	map = new Map();
	//Tiles
	tile0.AddComponent<TileComponent>(234, 234, 48, 48, 0);
	tile0.AddComponent<ColliderComponent>("water");
	tile1.AddComponent<TileComponent>(192, 192, 48, 48, 1);
	tile1.AddComponent<ColliderComponent>("grass");
	tile2.AddComponent<TileComponent>(336, 336, 48, 48, 2);
	tile2.AddComponent<ColliderComponent>("sand");
	//Player
	player.AddComponent<TransformComponent>(150, 0, 100, 100, 2);
	player.AddComponent<SpriteComponent>("res/out.png");
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>("player");
	//Wall
	wall.AddComponent<TransformComponent>(400.0f, 150.0f, 48, 48, 1);
	wall.AddComponent<SpriteComponent>("res/grass.png");
	wall.getComponent<TransformComponent>().height = 300;
	wall.AddComponent<ColliderComponent>("wall");

	//Trash for animation...
	tex1 = TextureManager::loadTexture("res/out.png");
	tex2 = TextureManager::loadTexture("res/out_1.png");
}
void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
	}
}

void Game::update() {
	manager.update();

	for (const auto& cc : colliders) {
		if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc) && cc->tag != "player") {
			std::cout << "Hit! - tag: " << cc->tag << std::endl;
		}
	}
}
void Game::render() {
	SDL_RenderClear(Game::renderer);
	//Write render
	map->drawMap();
	manager.draw();
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(Game::renderer, &player.getComponent<ColliderComponent>().collider);
	SDL_RenderDrawRect(Game::renderer, &wall.getComponent<ColliderComponent>().collider);
	//Write render
	SDL_RenderPresent(Game::renderer);
}
void Game::clean() {
	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Game quited" << std::endl;
}