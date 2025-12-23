#include "pch.h"
#include "Engine.h"
#include "scenes/custom/GameplayScene.h"
#include "scenes/custom/MenuScene.h"

Engine::Engine() {
	isRunning = false;
	window = nullptr;
	renderer = nullptr;
	auto highScores = scoreManager->Load();
}

Engine::~Engine() {
	scoreManager->Save("Player");

	if(renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if(window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}

void Engine::Init() {
	renderManager->LoadFont("res/fonts/PixelifySans-VariableFont_wght.ttf");

	renderManager->LoadTexture("res/bg.png");
	renderManager->LoadTexture("res/evil-woman.png");
	renderManager->LoadTexture("res/man.png");
	renderManager->LoadTexture("res/bullet.png");
	renderManager->LoadTexture("res/btn.png");
	renderManager->LoadTexture("res/black-screen.png");

	audioManager->LoadSoundData("res/audio/music/menace_title.wav");
	audioManager->LoadSoundData("res/audio/music/menace_subtune_2.wav");

	audioManager->LoadSoundData("res/audio/sfx/laserShoot.wav");
	audioManager->LoadSoundData("res/audio/sfx/ui_select.wav");
	audioManager->LoadSoundData("res/audio/sfx/ui_hover.wav");

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