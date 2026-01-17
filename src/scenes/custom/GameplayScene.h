#pragma once
#include "objects/custom/Bullet.h"
#include "objects/custom/Enemy.h"
#include "objects/custom/Player.h"
#include "objects/custom/ScrollingBackground.h"
#include "scenes/Scene.h"
#include <Managers/XMLReader.h>
#include <Objects/Button.h>
#include <Objects/custom/BackgroundDecorator.h>
#include <Objects/custom/Explosion.h>
#include <Objects/custom/TestAnimation.h>
#include <Objects/custom/Turret.h>
#include <Objects/PowerUps/PowerUp.h>
#include <objects/Enemies/BubbleEnemy.h>
#include <objects/Enemies/BioTitanEnemy.h>
#include <objects/Enemies/CirclerEnemy.h>
#include <objects/Enemies/KillerWhaleEnemy.h>
#include <objects/Enemies/MedusaEnemy.h>
#include <objects/Enemies/SpaceBoss.h>
#include <Objects/PowerUps/CannonEnergyPowerUp.h>
#include <objects/Text.h>
#include <objects/InputText.h>
#include <wave/Wave.h>

enum class GameplayState {
	GAMEPLAY,
	PAUSED,
	FINISH_STAGE,
	DEATH
};

class GameplayScene : public Scene {
private:
	GameplayState state = GameplayState::GAMEPLAY;
	bool stateJustChanged = false;
	float finishStageTimer = 0.f;

	//Player
	Player* player = Player::GetInstance();

	//Score UI
	Text* scoreText;
	Text* livesText;
	Text* scoreNumberText;

	//Score set UI
	Text* setScoreText;
	Text* userInputText;

	ScrollingBackground* currentBackground;

	unsigned int level = 0;
	bool bossSpawned = false;

public:
	GameplayScene() = default;
	void OnEnter() override {
		state = GameplayState::GAMEPLAY;
		stateJustChanged = false;
		finishStageTimer = 0.f;
		bossSpawned = false;
		WaveManager::GetInstance()->SetBossActive(false);

		if(level >= LEVEL_COUNT) level = 0;

		SpawnLevelBackground(level);
		LoadLevel(level);

		scoreText = new Text("Score");
		scoreText->GetTransform()->scale = { 2.f, 2.f };
		scoreText->GetTransform()->position = { 250, (float)RenderManager::GetInstance()->WINDOW_HEIGHT - 150 };
		ui.push_back(scoreText);

		scoreNumberText = new Text("000000");
		scoreNumberText->GetTransform()->scale = { 2.f, 2.f };
		scoreNumberText->GetTransform()->position = { 250, (float)RenderManager::GetInstance()->WINDOW_HEIGHT - 200 };
		ui.push_back(scoreNumberText);

		livesText = new Text("Lives: " + std::to_string(player->GetLives()));
		player->OnLivesChanged = [this](int current, int max) {
			livesText->SetText("Lives: " + std::to_string(player->GetLives()));
		};
		livesText->GetTransform()->scale = { 2.f, 2.f };
		livesText->GetTransform()->position = { 250, (float)RenderManager::GetInstance()->WINDOW_HEIGHT - 260 };
		ui.push_back(livesText);

		player->SetLayer(20);
		player->GetTransform()->position = { 0.f, 0.f };
		SpawnManager::Instance().SpawnObject(player);
		player->OnDeathEvent = [this]() {
			SetState(GameplayState::DEATH);
		};
		player->OnSceneEnter();

		BackgroundDecorator* decorator = new BackgroundDecorator();
		SpawnManager::Instance().SpawnObject(decorator);
	}

	void OnExit() override {
		TimeManager::GetInstance()->ClearAllEvents();
		player->OnLivesChanged = nullptr;
		WaveManager::GetInstance()->SetBossActive(false);

		Scene::OnExit();
	}

	void OnUpdate() override {
		bool stateChanged = stateJustChanged;

		switch(state) {
			case GameplayState::GAMEPLAY:
			UpdateGameplay();
			break;
			case GameplayState::PAUSED:
			UpdatePaused();
			break;
			case GameplayState::FINISH_STAGE:
			UpdateFinishStage();
			break;
			case GameplayState::DEATH:
			UpdateDeath();
			break;
		}

		if(stateChanged) stateJustChanged = false;

		scoreNumberText->SetText(ScoreManager::GetInstance()->GetScoreAsText());
		if(ScoreManager::GetInstance()->IsHighScore()) {
			scoreText->SetColor({ 0xff, 0xd7, 0x00, 0xff });
		}
	}

	void UpdateGameplay() {
		Scene::OnUpdate();

		if(InputManager::GetInstance()->GetEvent(SDLK_ESCAPE, DOWN)) {
			SetPauseMenuVisibility(true);
			SetState(GameplayState::PAUSED);
		}

		while(SpawnManager::Instance().AreObjectsPendingSpawn()) {
			objects.push_back(SpawnManager::Instance().GetSpawnedObject());
		}
	}

	void UpdatePaused() {
		UpdateUI();

		if(InputManager::GetInstance()->GetEvent(SDLK_ESCAPE, DOWN)) {
			SetPauseMenuVisibility(false);
			SetState(GameplayState::GAMEPLAY);
		}
	}

	void UpdateDeath() {
		if(stateJustChanged) {
			TimeManager::GetInstance()->SubscribeEvent(
				1.0f, [this]() {
				ShowDeathScreen();
			}
			);
		}
	}

	void UpdateFinishStage() {
		if(stateJustChanged) {
			userInputText = new InputText(" ");
			userInputText->GetTransform()->scale = { 2.f, 2.f };
			userInputText->GetTransform()->position = {
				RenderManager::GetInstance()->WINDOW_WIDTH / 2.0f - 100,
				RenderManager::GetInstance()->WINDOW_HEIGHT / 2.0f
			};
			setScoreText = new Text("Enter Name to set score: ");
			setScoreText->GetTransform()->scale = { 2.0f, 2.0f };
			setScoreText->GetTransform()->position = { 
				RenderManager::GetInstance()->WINDOW_WIDTH / 2.0f - 200, 
				RenderManager::GetInstance()->WINDOW_HEIGHT / 2.0f - 100
			};
			ui.push_back(userInputText);
			ui.push_back(setScoreText);
			return;
		}

		UpdateUI();

		// Wait for confirm
		if(InputManager::GetInstance()->GetEvent(SDLK_RETURN, DOWN) ||
		   InputManager::GetInstance()->GetGamepadButton(SDL_GAMEPAD_BUTTON_START)) {
			RecordHighScore();

			userInputText->Destroy();
			userInputText = nullptr;
			setScoreText->Destroy();
			setScoreText = nullptr;
		}
	}

	unsigned int GetLevel() { return level; }
	void SetLevel(unsigned int _level) {
		level = (_level < LEVEL_COUNT) ? _level : 0;
	}

private:
	void SetPauseMenuVisibility(bool visible) {
		if(visible) {
			Text* resumeText = new Text("Resume");
			resumeText->GetTransform()->scale = { 2,2 };
			Button* resumeBtn = new Button([this]() {
				SetPauseMenuVisibility(false);
				SetState(GameplayState::GAMEPLAY);
			}, resumeText);
			resumeBtn->GetTransform()->position = { (float)RenderManager::GetInstance()->WINDOW_WIDTH / 2.0f - 344.8f / 2, (float)RenderManager::GetInstance()->WINDOW_HEIGHT / 2.0f - 136.9f / 2 };
			ui.push_back(resumeBtn);
			ui.push_back(resumeText);
		}
		else {
			ui.back()->Destroy();
			ui[ui.size() - 2]->Destroy();
		}
	}

	void ShowDeathScreen() {
		Image* blackScreen = new Image(BLACK_SCREEN_SPRITE_PATH, Vector2(0, 0), Vector2((float)RenderManager::GetInstance()->WINDOW_WIDTH, (float)RenderManager::GetInstance()->WINDOW_HEIGHT));
		blackScreen->GetTransform()->position = { 0,0 };
		ui.push_back(blackScreen);
		TimeManager::GetInstance()->SubscribeEvent(
			2.0f, [this]() { ui.pop_back(); ExitDeath(); }
		);
	}

	void ExitDeath() {
		if(player->GetLives() > 0) {
			player->DecrementLives(1);
			player->HealToMax();
			player->GetTransform()->position = { 0, 0 };
			player->ResetForStage();
			bossSpawned = false;
			WaveManager::GetInstance()->SetBossActive(false);
			SpawnManager::Instance().ClearSpanwer();
			for(int i = 0; i < objects.size(); ++i) {
				Object* obj = objects[i];
				if(obj == player) continue;
				if(dynamic_cast<Enemy*>(obj) ||
				   dynamic_cast<Bullet*>(obj) ||
				   dynamic_cast<PowerUp*>(obj) ||
				   dynamic_cast<Explosion*>(obj) ||
				   dynamic_cast<Turret*>(obj)) {
					obj->Destroy();
				}
			}
			WaveManager::GetInstance()->RestartWave();
			this->SetState(GameplayState::GAMEPLAY);
		}
		else {
			this->SetState(GameplayState::FINISH_STAGE);
		}
	}

	void LoadLevel(int level) {
		WaveManager::GetInstance()->Clear();
		auto waves = XMLReader::Instance().FetchWavesFromFile(level);
		for(int i = 0; i < waves.size(); i++) {
			waves[i].OnWaveFinishedSpawning = [this]() { std::cout << "Wave finished spawning\n"; }; //DEBUG
			WaveManager::GetInstance()->AddWave(std::move(waves[i]));
		}
		WaveManager::GetInstance()->OnWaveCleared = [this](int waveIndex) {
			if(!WaveManager::GetInstance()->AreAllWavesFinished()) return;
			if(!bossSpawned) {
				bossSpawned = true;
				SpawnBossForLevel();
				return;
			}
			SetState(GameplayState::FINISH_STAGE);
		};
		WaveManager::GetInstance()->Start();
	}

	void SpawnLevelBackground(int level) {
		std::string bgTexture;
		switch(level) {
			case 0: bgTexture = BACKGROUND_SPRITE_LVL1_PATH; break;
			case 1: bgTexture = BACKGROUND_SPRITE_LVL2_PATH; break;
			case 2: bgTexture = BACKGROUND_SPRITE_LVL3_PATH; break;
			default: bgTexture = BACKGROUND_SPRITE_LVL1_PATH; break;
		}
		currentBackground = new ScrollingBackground(bgTexture, BACKGROUND_SPEED, -1000);
		currentBackground->SetLayer(-99);
		SpawnManager::Instance().SpawnObject(currentBackground);
	}

	void SpawnBossForLevel() {
		Enemy* boss = nullptr;
		Vector2 spawnPos = {
			RenderManager::GetInstance()->WINDOW_WIDTH - 200.f,
			RenderManager::GetInstance()->WINDOW_HEIGHT / 2.f
		};

		if(level == 0) {
			boss = new BioTitanEnemy(spawnPos);
		}
		else {
			boss = new SpaceBoss(spawnPos);
		}

		if(boss) {
			WaveManager::GetInstance()->SetBossActive(true);
			SpawnManager::Instance().SpawnObject(boss);
		}
	}

	void SetState(GameplayState _state) {
		state = _state;
		stateJustChanged = true;

		if(state == GameplayState::FINISH_STAGE) {
			SpawnManager::Instance().DestroyAllOfType<Bullet>();
		}
	}

	bool AreEnemiesRemaining() {
		for(Object* obj : objects) {
			Enemy* enemy;
			if(enemy = dynamic_cast<Enemy*>(obj)) return true;
		}
		return false;
	}

	void RecordHighScore() {
		//TODO: Hook up to file manager
		ScoreManager::GetInstance()->Save(userInputText->GetText());
		SceneManager::GetInstance()->SetNextScene(SceneState::MENU);
	}
};
