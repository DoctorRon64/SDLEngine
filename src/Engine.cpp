#include "pch.h"
#include "Engine.h"
#include "scenes/custom/GameplayScene.h"
#include "scenes/custom/LevelSelectScene.h"
#include "scenes/custom/MenuScene.h"
#include "scenes/custom/RankingScene.h"
#include "scenes/custom/SplashScreenScene.h"

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
		SceneManager::GetInstance()->AddScene(SceneState::LEVEL_SELECT, new LevelSelectScene());
		SceneManager::GetInstance()->InitFirstScene(SceneState::SPLASH);
	}
	catch(const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	isRunning = true;
}

void Engine::LoadAssets() {
	RenderManager::GetInstance()->LoadFont(FONT_PATH);

	RenderManager::GetInstance()->LoadTexture(ENEMY_AMOEBA_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_BEHOLDER_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_BUBBLE_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_CHOMPER_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_CIRCLER_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_MEDUSA_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_VERTICAL_MEDUSA_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_WHALE_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_BIO_TITAN_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_TORPEDO_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_TURBO_CHAINSAW_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_ROBO_KRABS_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_NUKE_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_MISSILE_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_DANIELS_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_UFO_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_ANNOYER_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_ANGRYGON_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_SPACE_BOSS_SPRITE_PATH);

	RenderManager::GetInstance()->LoadTexture(BACKGROUND_SPRITE_LVL1_PATH);
	RenderManager::GetInstance()->LoadTexture(BACKGROUND_SPRITE_LVL2_PATH);
	RenderManager::GetInstance()->LoadTexture(BACKGROUND_SPRITE_LVL3_PATH);
	RenderManager::GetInstance()->LoadTexture(PLAYER_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(BULLET_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(BUTTON_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(BLACK_SCREEN_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(SPLASH_SCREEN_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(EXPLOSION_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(DECORATION_GRASS_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(DECORATION_BUSH_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(DECORATION_FLOWER_SPRITE_PATH);

	AudioManager::GetInstance()->LoadSoundData(MUSIC_MENACE_SUBTUNE_2_PATH);
	AudioManager::GetInstance()->LoadSoundData(MUSIC_MENACE_TITLE_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_LASER_SHOOT_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_UI_SELECT_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_UI_HOVER_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_HURT_BULLET_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_HURT_ENEMY_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_HURT_PLAYER_PATH);
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
