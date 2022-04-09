#include "Game.h"

//Penis PLOW
int main(int argc, char* argv[] ) {
	
	const int FPS = 60; // target fps
	const int FRAME_DELAY = 1000 / FPS; // 16.6ms

	Uint32 frameStart;
	int frameTime;
	
	Game g;
	g.init("TIoW - Tea instead of whiskey", 555, 555, 640, 480, false);

	while (g.running()) {
		frameStart = SDL_GetTicks(); //time Starts
		
		g.handleEvents();
		g.update();
		g.render();
	
		frameTime = SDL_GetTicks() - frameStart; //time Ends

		if (frameTime < FRAME_DELAY) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}

	g.clean();

	return 0;
}
