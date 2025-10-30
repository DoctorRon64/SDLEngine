#include "Engine.h"
#include <Objects/ImageObject.h>

void Engine::Init() {
	InitSDL();
	CreateWindowAndRenderer();

	SDL_SetRenderDrawColor(renderer, 100, 250, 230, 0xff);
	isRunning = true;

	gameObjects.push_back(new ImageObject("res/ship.jpg", renderer));
}

void Engine::HandleEvents() {
	SDL_Event event;

	//Handle winow events
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
		case  SDL_EVENT_QUIT:
			isRunning = false;
			break;
		}
	}
}

void Engine::Update() {
	for(Object* obj : gameObjects) {
		obj->Update();
	}
}

void Engine::InitSDL() {
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		throw SDL_GetError();
	}
}

void Engine::CreateWindowAndRenderer() {
	if(!SDL_CreateWindowAndRenderer("Main Window", windowSizeX, windowSizeY, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		throw SDL_GetError();
	}
}

void Engine::Render() {
	SDL_RenderClear(renderer);
	for(Object* obj : gameObjects) {
		obj->Render(renderer);
	}
	SDL_RenderPresent(renderer);
}

void Engine::Terminate() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}