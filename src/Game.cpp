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

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

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
	map->loadMapFromFile("res/Untitled.pyxel", 10, 10);
	//Player
	player.AddComponent<TransformComponent>(150, 0, 100, 100, 2);
	player.AddComponent<SpriteComponent>("res/out.png", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>("player");
	player.addGroup(groupLabels::groupPlayers);
	//Wall
	wall.AddComponent<TransformComponent>(400.0f, 150.0f, 48, 48, 1);
	wall.AddComponent<SpriteComponent>("res/grass.png");
	wall.getComponent<TransformComponent>().height = 300;
	wall.AddComponent<ColliderComponent>("wall");
	wall.addGroup(groupLabels::groupMap);
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

auto& tiles(manager.getGroup(groupLabels::groupMap));
auto& players(manager.getGroup(groupLabels::groupPlayers));
auto& enemies(manager.getGroup(groupLabels::groupEnemies));

void Game::render() {
	SDL_RenderClear(Game::renderer);
	//Write render
	for (auto& t : tiles)
		t->draw();
	for (auto& p : players)
		p->draw();
	for (auto& e : enemies)
		e->draw();
	SDL_SetRenderDrawColor(Game::renderer, 205, 0, 148, 255);
	SDL_RenderDrawRect(Game::renderer, &player.getComponent<ColliderComponent>().collider);
	//Write render
	SDL_RenderPresent(Game::renderer);
}
void Game::clean() {
	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Game quited" << std::endl;
}
void Game::AddTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.AddComponent<TileComponent>(x, y, 48, 48, id);
	tile.addGroup(groupLabels::groupMap);
}