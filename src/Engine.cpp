#include "pch.h"
#include "Engine.h"
#include "Objects/Object.h"
#include "Objects/TestObject.h"

void Engine::Init() {
	renderManager->LoadTexture("res/ship.jpg");

	isRunning = true;

	TestObject* test1 = new TestObject();
	gameObjects.push_back(test1);
	TestObject* test2 = new TestObject();
	gameObjects.push_back(test2);
}

void Engine::HandleEvents() {
	//SDL_Event event;

	//while(SDL_PollEvent(&event)) {
	//	switch(event.type) {
	//		case  SDL_EVENT_QUIT:
	//		isRunning = false;
	//		break;
	//	}
	//}

	isRunning = !inputManager->Listen();
}

void Engine::Update() {
	for(Object* obj : gameObjects) {
		obj->Update();
	}

	if(inputManager->GetEvent(SDLK_S, DOWN)) {
		std::cout << "something happend yeeess" << std::endl;
	}
}

void Engine::Render() {
	renderManager->ClearScreen();

	for(Object* obj : gameObjects) {
		obj->Render();
	}

	renderManager->RenderScreen();
}