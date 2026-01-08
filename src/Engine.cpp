#include "pch.h"
#include "Engine.h"
#include "scenes/custom/GameplayScene.h"
#include "scenes/custom/MenuScene.h"
#include "scenes/custom/SplashScreenScene.h"
#include "scenes/custom/RankingScene.h"

Engine::Engine() {
	isRunning = false;
	window = nullptr;
	renderer = nullptr;
	auto highScores = ScoreManager::GetInstance()->Load();
}

Engine::~Engine() {
	ScoreManager::GetInstance()->Save("Player");

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
	LoadAssets();

	try {
		SceneManager::GetInstance()->AddScene(SceneState::SPLASH, new SplashScreenScene());
		SceneManager::GetInstance()->AddScene(SceneState::MENU, new MenuScene());
		SceneManager::GetInstance()->AddScene(SceneState::GAMEPLAY, new GameplayScene());
		SceneManager::GetInstance()->AddScene(SceneState::RANKING, new RankingScene());
		SceneManager::GetInstance()->InitFirstScene(SceneState::SPLASH);
	}
	catch(const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	isRunning = true;
}

void Engine::LoadAssets() {
	RenderManager::GetInstance()->LoadFont("res/fonts/PixelifySans-VariableFont_wght.ttf");

	RenderManager::GetInstance()->LoadTexture("res/enemies/bubble_sprite.png");
	RenderManager::GetInstance()->LoadTexture("res/enemies/circler_sprite.png");
	RenderManager::GetInstance()->LoadTexture("res/enemies/medusa_sprite.png");
	RenderManager::GetInstance()->LoadTexture("res/enemies/whale_sprite.png");

	RenderManager::GetInstance()->LoadTexture("res/bg.png");
	RenderManager::GetInstance()->LoadTexture("res/player_sprite.png");
	RenderManager::GetInstance()->LoadTexture("res/bullet.png");
	RenderManager::GetInstance()->LoadTexture("res/btn.png");
	RenderManager::GetInstance()->LoadTexture("res/black-screen.png");
	RenderManager::GetInstance()->LoadTexture("res/splash_screen.png");
	RenderManager::GetInstance()->LoadTexture("res/explosion.png");

	AudioManager::GetInstance()->LoadSoundData("res/audio/music/menace_subtune_2.wav");
	AudioManager::GetInstance()->LoadSoundData("res/audio/music/menace_title.wav");

	AudioManager::GetInstance()->LoadSoundData("res/audio/sfx/laserShoot.wav");
	AudioManager::GetInstance()->LoadSoundData("res/audio/sfx/ui_select.wav");
	AudioManager::GetInstance()->LoadSoundData("res/audio/sfx/ui_hover.wav");
}

void Engine::HandleEvents() {
	isRunning = !InputManager::GetInstance()->Listen();
}

void Engine::Update() {
	SceneManager::GetInstance()->UpdateCurrentScene();
}

void Engine::Render() {
	RenderManager::GetInstance()->ClearScreen();
	SceneManager::GetInstance()->GetCurrentScene()->Render();
	RenderManager::GetInstance()->RenderScreen();
}