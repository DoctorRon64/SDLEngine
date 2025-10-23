#include <SDL3/SDL.h>
#include <iostream>

int main() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		throw SDL_GetError();
	}

	std::cout << "AYUDAAAAA!!!" << std::endl;
	return 0;
}