#include "pch.h"
#include "Engine.h"
#include "scenes/custom/GameplayScene.h"
#include "scenes/custom/MenuScene.h"

void Engine::Init() {
	renderManager->LoadFont("res/fonts/Fredoka.ttf");

	try {
		sceneManager->AddScene(MENU, new MenuScene());
		sceneManager->AddScene(GAMEPLAY, new GameplayScene());
		sceneManager->InitFirstScene(MENU);
	}
	catch(const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	isRunning = true;
}

void Engine::HandleEvents() {
	isRunning = !inputManager->Listen();
}

void Engine::Update() {
	sceneManager->UpdateCurrentScene();
	/*if(inputManager->GetEvent(SDLK_S, DOWN)) {
		std::cout << "something happend yeeess" << std::endl;
	}*/
}

void Engine::Render() {
	renderManager->ClearScreen();
	sceneManager->GetCurrentScene()->Render();
	renderManager->RenderScreen();
}