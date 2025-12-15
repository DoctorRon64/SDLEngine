#include "pch.h"
#include "Engine.h"
#include "scenes/custom/GameplayScene.h"
#include "scenes/custom/MenuScene.h"

Engine::Engine() {
	isRunning = false;
	window = nullptr;
	renderer = nullptr;
}

Engine::~Engine() {
	delete window;
	delete renderer;
}

void Engine::Init() {
	renderManager->LoadFont("res/fonts/Fredoka.ttf");
	renderManager->LoadTexture("res/bg.jpg");
	renderManager->LoadTexture("res/evil-woman.png");
	renderManager->LoadTexture("res/man.png");
	renderManager->LoadTexture("res/bullet.png");

	try {
		sceneManager->AddScene(SceneState::MENU, new MenuScene());
		sceneManager->AddScene(SceneState::GAMEPLAY, new GameplayScene());
		sceneManager->InitFirstScene(SceneState::MENU);
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
}

void Engine::Render() {
	renderManager->ClearScreen();
	sceneManager->GetCurrentScene()->Render();
	renderManager->RenderScreen();
}