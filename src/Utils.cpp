#include "Utils.h"

void printError(const std::string& message) {
	std::cerr << "Couldn't create window!: " << SDL_GetError() << std::endl;
	SDL_ClearError();
}
