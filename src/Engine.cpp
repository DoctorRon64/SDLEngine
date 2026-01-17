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
	ScoreManager::GetInstance()->Init();
}

Engine::~Engine() {
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
	RenderManager::GetInstance()->LoadTexture(MENU_SCREEN_PATH);
	RenderManager::GetInstance()->LoadTexture(LEVEL_SELECT_SCREEN_PATH);
	RenderManager::GetInstance()->LoadTexture(RANKING_SCREEN_PATH);
	RenderManager::GetInstance()->LoadTexture(RANKING_PANEL_PATH);

	RenderManager::GetInstance()->LoadTexture(PLAYER_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(TURRET_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(BULLET_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(ENEMY_BULLET_SPRITE_PATH);
	RenderManager::GetInstance()->LoadTexture(POWERUP_SPRITE_PATH);
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
	AudioManager::GetInstance()->LoadSoundData(SFX_EXPLOSION_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_POWERUP_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_PLAYER_IMPACT_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_BOSS_SPAWN_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_BOSS_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_GAME_WIN_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_GAME_LOSE_PATH);

	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_AMOEBA_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_BEHOLDER_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_BUBBLE_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_CHOMPER_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_CIRCLER_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_MEDUSA_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_VERTICAL_MEDUSA_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_WHALE_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_TORPEDO_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_TURBO_CHAINSAW_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_ROBO_KRABS_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_NUKE_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_MISSILE_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_DANIELS_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_UFO_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_ANNOYER_DEATH_PATH);
	AudioManager::GetInstance()->LoadSoundData(SFX_ENEMY_ANGRYGON_DEATH_PATH);
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
