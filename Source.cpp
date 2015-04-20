/*************************************************************/
//					Tic Tac Toe Project
/*************************************************************/
#include "SDLClass.h"

int main(int argc, char* args[])
{
	MySDL2 *sdl = new MySDL2;
	bool quit = false;
	SDL_Event e;

	if (!sdl->init()) { cout << "Failed to initialize!\n"; quit = true; }
	if (!sdl->loadMedia("viewport.png")) { cout << "Failed to load media!\n"; quit = true; }

	// Main loop
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}
		sdl->renderClear();
		sdl->render();
		sdl->renderUpdate();
	}

	sdl->~MySDL2();

	delete sdl;

	return 0;
}