#include <iostream>
#include <string>
#include <cmath>

#if _WIN32
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_mixer.h>
#else
#include <SDL2\SDL.h>
#include <SDL\SDL_image.h>
#include <SDL\SDL_mixer.h>
#endif

using std::string;
using std::cout;

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer.lib")