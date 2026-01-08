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
#include <objects/Enemies/BubbleEnemy.h>
#include <objects/Enemies/CirclerEnemy.h>
#include <objects/Enemies/KillerWhaleEnemy.h>
#include <objects/Enemies/MedusaEnemy.h>
#include <Objects/PowerUps/CannonEnergyPowerUp.h>
#include <objects/Text.h>
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

	//Player
	Player* player = Player::GetInstance();

	//Score UI
	Text* scoreText;
	Text* livesText;
	Text* scoreNumberText;

	//Score set UI
	Text* setScoreText;
	Text* setScoreNameText;

	unsigned int level;

public:
	GameplayScene() = default;
	void OnEnter() override {
		std::cout << level << std::endl;

		ScrollingBackground* bg = new ScrollingBackground("res/bg.png", BACKGROUND_SPEED, -1000);
		SpawnManager::Instance().SpawnObject(bg);

		Wave wave1 = XMLReader::Instance().FetchWave(level, 0);
		Wave wave2 = XMLReader::Instance().FetchWave(level, 1);
		Wave wave3 = XMLReader::Instance().FetchWave(level, 1);
		Wave wave4 = XMLReader::Instance().FetchWave(level, 1);
		Wave wave5 = XMLReader::Instance().FetchWave(level, 1);
		Wave wave6 = XMLReader::Instance().FetchWave(level, 1);
		Wave wave7 = XMLReader::Instance().FetchWave(level, 1);
		WaveManager::GetInstance()->AddWave(std::move(wave1));
		WaveManager::GetInstance()->AddWave(std::move(wave2));
		WaveManager::GetInstance()->AddWave(std::move(wave3));
		WaveManager::GetInstance()->AddWave(std::move(wave4));
		WaveManager::GetInstance()->AddWave(std::move(wave5));
		WaveManager::GetInstance()->AddWave(std::move(wave6));
		WaveManager::GetInstance()->AddWave(std::move(wave7));
		WaveManager::GetInstance()->Start();

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

		setScoreText = new Text("Enter Name: ");
		setScoreText->GetTransform()->scale = { 2.0f, 2.0f };
		setScoreText->GetTransform()->position = { RenderManager::GetInstance()->WINDOW_WIDTH / 2.0f, RenderManager::GetInstance()->WINDOW_HEIGHT / 2.0f };
		setScoreNameText = new Text(" ");
		setScoreNameText->GetTransform()->scale = { 2.0f, 2.0f };
		setScoreNameText->GetTransform()->position = { RenderManager::GetInstance()->WINDOW_WIDTH / 2.0f + 300.0f, RenderManager::GetInstance()->WINDOW_HEIGHT / 2.0f };

		player->SetLayer(20);
		SpawnManager::Instance().SpawnObject(player);
		player->OnDeath = [this]() {
			SetState(GameplayState::DEATH);
		};
		player->OnSceneEnter();

		Explosion* testAnim = new Explosion();
		testAnim->GetTransform()->position = { (float)RenderManager::GetInstance()->WINDOW_WIDTH / 2, (float)RenderManager::GetInstance()->WINDOW_HEIGHT / 2 };
		testAnim->SetLayer(20);
		SpawnManager::Instance().SpawnObject(testAnim);

		BackgroundDecorator* decorator = new BackgroundDecorator();
		SpawnManager::Instance().SpawnObject(decorator);
	}

	void OnExit() override {
		TimeManager::GetInstance()->ClearAllEvents();
		player->OnLivesChanged = nullptr;

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

		if(WaveManager::GetInstance()->IsCurrentWaveFinishedSpawning() &&
			!AreEnemiesRemaining()) {
			SetState(GameplayState::FINISH_STAGE);
		}
	}

	void UpdatePaused() {
		if(InputManager::GetInstance()->GetEvent(SDLK_ESCAPE, DOWN)) {
			SetPauseMenuVisibility(false);
			SetState(GameplayState::GAMEPLAY);
		}
	}

	void UpdateDeath() {
		if(stateJustChanged) {
			TimeManager::GetInstance()->SubscribeEvent(
				1.0f, [this]() { ShowDeathScreen(); }
			);
		}
	}

	void UpdateFinishStage() {
		if(WaveManager::GetInstance()->AreAllWavesFinishedSpawning()) {
			RecordHighScore();
		}
		else {
			//TODO: Finish Stage Transition
			WaveManager::GetInstance()->StartNextWave();
			SetState(GameplayState::GAMEPLAY);
		}
	}

	unsigned int GetLevel() { return level; }
	void SetLevel(unsigned int _level) { level = _level; }

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
		Image* blackScreen = new Image("res/black-screen.png", Vector2(0, 0), Vector2((float)RenderManager::GetInstance()->WINDOW_WIDTH, (float)RenderManager::GetInstance()->WINDOW_HEIGHT));
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
			for(int i = 0; i < objects.size(); ++i) {
				Enemy* enemy;
				if(enemy = dynamic_cast<Enemy*>(objects[i])) {
					objects[i]->Destroy();
				}
			}
			WaveManager::GetInstance()->RestartWave();
			this->SetState(GameplayState::GAMEPLAY);
		}
		else {
			RecordHighScore();
		}
	}

	void SetState(GameplayState _state) {
		state = _state;
		stateJustChanged = true;
	}

	bool AreEnemiesRemaining() {
		for(Object* obj : objects) {
			Enemy* enemy;
			if(enemy = dynamic_cast<Enemy*>(obj)) return true;
		}
		return false;
	}

	void RecordHighScore() {
		if(stateJustChanged) {
			ui.push_back(setScoreText);
			ui.push_back(setScoreNameText);
			std::cout << "Set Score";
		}
		for(Sint32 key = SDLK_A; key < SDLK_Z; ++key) {
			if(InputManager::GetInstance()->GetEvent(key, DOWN)) {
				std::string name = setScoreNameText->GetText();
				char letter = key - SDLK_A + 'A';
				name += letter;
				setScoreNameText->SetText(name);
				break;
			}
		}
		if(InputManager::GetInstance()->GetEvent(SDLK_RETURN, DOWN)) {
			//TODO: Hook up to file manager
			SceneManager::GetInstance()->SetNextScene(SceneState::MENU);
		}
	}
};