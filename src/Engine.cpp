#include "pch.h"
#include "Engine.h"
#include "managers/SceneManager.h"
#include "Objects/TestObject.h"
#include "scenes/custom/GameplayScene.h"

void Engine::Init() {
	renderManager->LoadTexture("res/ship.jpg");

	try {
		sceneManager->AddScene("Gameplay", new GameplayScene());
		sceneManager->InitFirstScene("Gameplay");
	}
	catch(const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	isRunning = true;

	TestObject* test1 = new TestObject();
	gameObjects.push_back(test1);
	TestObject* test2 = new TestObject();
	gameObjects.push_back(test2);
}

void Engine::HandleEvents() {
	isRunning = !inputManager->Listen();
}

void Engine::Update() {
	sceneManager->UpdateCurrentScene();

	if(inputManager->GetEvent(SDLK_S, DOWN)) {
		std::cout << "something happend yeeess" << std::endl;
	}
}

void Engine::Render() {
	renderManager->ClearScreen();
	sceneManager->GetCurrentScene()->Render();
	renderManager->RenderScreen();
}