#include "Engine.h"
#include "Objects/ImageObject.h"
#include "Objects/TestObject.h"

void Engine::Init() {
	renderManager->Init();
	renderManager->LoadTexture("res/ship.jpg");

	isRunning = true;

	TestObject* test1 = new TestObject();
	gameObjects.push_back(test1);
	TestObject* test2 = new TestObject();
	gameObjects.push_back(test2);
}

void Engine::HandleEvents() {
	SDL_Event event;

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

void Engine::Render() {
	renderManager->ClearScreen();

	for(Object* obj : gameObjects) {
		obj->Render();
	}

	renderManager->RenderScreen();
}