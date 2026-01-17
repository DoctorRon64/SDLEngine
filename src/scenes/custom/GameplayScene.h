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
	Text* scoreText = nullptr;
	Text* livesText = nullptr;
	Text* scoreNumberText = nullptr;
	Text* bestScoreText = nullptr;
	Text* bestScoreNumberText = nullptr;

	//Score set UI
	Text* setScoreText = nullptr;
	Text* userInputText = nullptr;
	Text* confirmHintText = nullptr;
	Image* scoreInputPanel = nullptr;
	Image* scoreInputBox = nullptr;
	Image* deathOverlay = nullptr;

	ScrollingBackground* currentBackground;

	unsigned int level = 0;
	bool bossSpawned = false;
	bool bossSeen = false;
	bool wonStage = false;
	bool bonusApplied = false;

public:
	GameplayScene() = default;
	void OnEnter() override {
		state = GameplayState::GAMEPLAY;
		stateJustChanged = false;
		finishStageTimer = 0.f;
		bossSpawned = false;
		bossSeen = false;
		wonStage = false;
		bonusApplied = false;
		WaveManager::GetInstance()->SetBossActive(false);
		ScoreManager::GetInstance()->ResetScore();

		AudioManager::GetInstance()->PlaySoundLooping(MUSIC_MENACE_SUBTUNE_2_PATH);

		if(level >= LEVEL_COUNT) level = 0;

		SpawnLevelBackground(level);
		LoadLevel(level);

		const float hudX = 40.0f;
		const float hudLine = 30.0f;
		const float hudBottom = (float)RenderManager::GetInstance()->WINDOW_HEIGHT - 70.0f;

		scoreText = new Text("Score: 000000", { 0xff, 0xe2, 0x6a, 0xff });
		scoreText->GetTransform()->scale = { 1.6f, 1.6f };
		scoreText->GetTransform()->position = { hudX, hudBottom - hudLine * 2.0f };
		ui.push_back(scoreText);

		livesText = new Text("Lives: " + std::to_string(player->GetLives()), { 0xff, 0xff, 0xff, 0xff });
		player->OnLivesChanged = [this](int current, int max) {
			livesText->SetText("Lives: " + std::to_string(player->GetLives()));
		};
		livesText->GetTransform()->scale = { 1.4f, 1.4f };
		livesText->GetTransform()->position = { hudX, hudBottom };
		ui.push_back(livesText);

		bestScoreText = new Text("Best: " + ScoreManager::GetInstance()->GetBestScoreAsText(), { 0x7c, 0xd7, 0xff, 0xff });
		bestScoreText->GetTransform()->scale = { 1.6f, 1.6f };
		bestScoreText->GetTransform()->position = { hudX, hudBottom - hudLine };
		ui.push_back(bestScoreText);

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
		deathOverlay = nullptr;
		scoreInputPanel = nullptr;
		scoreInputBox = nullptr;
		confirmHintText = nullptr;

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

		scoreText->SetText("Score: " + ScoreManager::GetInstance()->GetScoreAsText());
		bestScoreText->SetText("Best: " + ScoreManager::GetInstance()->GetBestScoreAsText());
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

		WaveManager::GetInstance()->CheckWaveCleared();

		if(state != GameplayState::GAMEPLAY) return;

		bool bossPresent = false;
		for(Object* obj : objects) {
			if(dynamic_cast<SpaceBoss*>(obj) || dynamic_cast<BioTitanEnemy*>(obj)) {
				bossPresent = true;
				break;
			}
		}
		if(bossPresent) {
			bossSeen = true;
		}

		if(bossSpawned && bossSeen && !bossPresent &&
		   WaveManager::GetInstance()->IsCurrentWaveFinishedSpawning() &&
		   !AreEnemiesRemaining()) {
			WaveManager::GetInstance()->SetBossActive(false);
			if(!bonusApplied) {
				ScoreManager::GetInstance()->AddScore(LEVEL_CLEAR_BONUS_PER_LIFE * player->GetLives());
				bonusApplied = true;
			}
			wonStage = true;
			SetState(GameplayState::FINISH_STAGE);
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
			AudioManager::GetInstance()->PlaySound(wonStage ? SFX_GAME_WIN_PATH : SFX_GAME_LOSE_PATH);
			const Vector2 panelTextureSize = { 700.f, 480.f };
			const Vector2 panelSize = { 520.f, 220.f };
			const float panelLeft = RenderManager::GetInstance()->WINDOW_WIDTH * 0.5f - panelSize.x * 0.5f;
			const float panelTop = RenderManager::GetInstance()->WINDOW_HEIGHT * 0.5f - panelSize.y * 0.5f;

			scoreInputPanel = new Image(RANKING_PANEL_PATH, { 0, 0 }, panelTextureSize);
			scoreInputPanel->GetTransform()->scale = { panelSize.x / panelTextureSize.x, panelSize.y / panelTextureSize.y };
			scoreInputPanel->GetTransform()->position = { panelLeft, panelTop };
			ui.push_back(scoreInputPanel);

			const Vector2 boxSize = { 320.f, 60.f };
			scoreInputBox = new Image(BUTTON_SPRITE_PATH, { 0, 0 }, { 3448.f, 1369.f });
			scoreInputBox->GetTransform()->scale = { boxSize.x / 3448.f, boxSize.y / 1369.f };
			scoreInputBox->GetTransform()->position = { panelLeft + 40.0f, panelTop + 90.0f };
			ui.push_back(scoreInputBox);

			setScoreText = new Text("ENTER YOUR NAME", { 0x00, 0x00, 0x00, 0xff });
			setScoreText->GetTransform()->scale = { 1.4f, 1.4f };
			setScoreText->GetTransform()->position = { panelLeft + 40.0f, panelTop + 30.0f };
			ui.push_back(setScoreText);

			userInputText = new InputText(" ");
			userInputText->SetColor({ 0x00, 0x00, 0x00, 0xff });
			userInputText->GetTransform()->scale = { 1.6f, 1.6f };
			userInputText->GetTransform()->position = { panelLeft + 55.0f, panelTop + 100.0f };
			ui.push_back(userInputText);

			confirmHintText = new Text("PRESS ENTER TO CONFIRM", { 0x00, 0x00, 0x00, 0xff });
			confirmHintText->GetTransform()->scale = { 1.0f, 1.0f };
			confirmHintText->GetTransform()->position = { panelLeft + 40.0f, panelTop + 160.0f };
			ui.push_back(confirmHintText);
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
			if(confirmHintText) {
				confirmHintText->Destroy();
				confirmHintText = nullptr;
			}
			if(scoreInputBox) {
				scoreInputBox->Destroy();
				scoreInputBox = nullptr;
			}
			if(scoreInputPanel) {
				scoreInputPanel->Destroy();
				scoreInputPanel = nullptr;
			}
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
		if(deathOverlay) {
			deathOverlay->Destroy();
			deathOverlay = nullptr;
		}
		deathOverlay = new Image(BLACK_SCREEN_SPRITE_PATH, Vector2(0, 0), Vector2((float)RenderManager::GetInstance()->WINDOW_WIDTH, (float)RenderManager::GetInstance()->WINDOW_HEIGHT));
		deathOverlay->GetTransform()->position = { 0,0 };
		ui.push_back(deathOverlay);
		TimeManager::GetInstance()->SubscribeEvent(
			2.0f, [this]() {
			if(deathOverlay) {
				deathOverlay->Destroy();
				deathOverlay = nullptr;
			}
			ExitDeath();
		}
		);
	}

	void ExitDeath() {
		if(player->GetLives() > 0) {
			player->DecrementLives(1);
			player->HealToMax();
			player->GetTransform()->position = { 0, 0 };
			player->ResetForStage();
			bossSpawned = false;
			bossSeen = false;
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
			wonStage = false;
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
			if(!bonusApplied) {
				ScoreManager::GetInstance()->AddScore(LEVEL_CLEAR_BONUS_PER_LIFE * player->GetLives());
				bonusApplied = true;
			}
			wonStage = true;
			SetState(GameplayState::FINISH_STAGE);
		};
		WaveManager::GetInstance()->OnWaveStarted = [this](int waveIndex) {
			ScrollingBackground* bg = nullptr;
			for(Object* obj : objects) {
				if(obj == currentBackground) {
					bg = currentBackground;
					break;
				}
			}
			if(!bg) bg = FindBackground();
			if(bg) {
				currentBackground = bg;
				currentBackground->Reset();
			}
		};
		WaveManager::GetInstance()->Start();
	}

	void SpawnLevelBackground(int level) {
		std::string bgTexture;
		switch(level) {
			case 0: bgTexture = BACKGROUND_SPRITE_LVL1_PATH; break;
			case 1: bgTexture = BACKGROUND_SPRITE_LVL2_PATH; break;
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
			AudioManager::GetInstance()->PlaySound(SFX_BOSS_SPAWN_PATH);
		}
	}

	void SetState(GameplayState _state) {
		state = _state;
		stateJustChanged = true;

		if(state == GameplayState::FINISH_STAGE) {
			SpawnManager::Instance().DestroyAllOfType<Bullet>();
		}
	}

	ScrollingBackground* FindBackground() {
		for(Object* obj : objects) {
			if(auto* bg = dynamic_cast<ScrollingBackground*>(obj)) return bg;
		}
		return nullptr;
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
