#include "Engine.h"

void Engine::Init() {
	InitSDL();
	CreateWindowAndRenderer();

	SDL_SetRenderDrawColor(renderer, 100, 250, 230, 0xff);
	isRunning = true;

	gameObjects.push_back(GameObject("res/ship.jpg", renderer));
}

void Engine::HandleEvents() {
	SDL_Event event;

	//Handle winow events
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case  SDL_EVENT_QUIT:
			isRunning = false;
			break;
		}
	}
}

void Engine::Update() {
	for (GameObject& obj : gameObjects) {
		obj.Update();
	}
}

void Engine::InitSDL() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		throw SDL_GetError();
	}
}

void Engine::CreateWindowAndRenderer() {
	if (!SDL_CreateWindowAndRenderer("Main Window", windowX, windowY, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		throw SDL_GetError();
	}
}

void Engine::Render() {
	SDL_RenderClear(renderer);
	for (GameObject& obj : gameObjects) {
		obj.Render(renderer);
	}
	SDL_RenderPresent(renderer);
}

void Engine::Terminate()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}