#pragma once
#include "objects/custom/Bullet.h"
#include "objects/custom/Enemy.h"
#include "objects/custom/Player.h"
#include "objects/custom/ScrollingBackground.h"
#include "scenes/Scene.h"
#include <Objects/Button.h>
#include <objects/Enemies/BubbleEnemy.h>
#include <objects/Enemies/CirclerEnemy.h>
#include <objects/Enemies/KillerWhaleEnemy.h>
#include <objects/Enemies/MedusaEnemy.h>
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
	Player* player = new Player();

	//Score UI
	Text* scoreText = new Text("Score");
	Text* scoreNumberText = new Text("000000");

	//Score set UI
	Text* setScoreText = new Text("Enter Name: ");
	Text* setScoreNameText = new Text(" ");

public:
	GameplayScene() = default;
	void OnEnter() override {
		ScrollingBackground* bg = new ScrollingBackground("res/bg.png", 200.0f, -1000);
		spawnManager.SpawnObject(bg);

		Wave wave1;
		wave1.AddSpawn(0.0f, []() { spawnManager.SpawnObject(new BubbleEnemy({ 1400.f, 200.f })); });
		wave1.AddSpawn(0.5f, []() { spawnManager.SpawnObject(new MedusaEnemy({ 1400.f, 400.f })); });
		wave1.AddSpawn(0.5f, []() { spawnManager.SpawnObject(new KillerWhaleEnemy({ 1400.f, 600.f })); });
		wave1.AddSpawn(1.0f, []() { spawnManager.SpawnObject(new CirclerEnemy({ 1200.f, 300.f })); });
		waveManager->AddWave(std::move(wave1));
		waveManager->Start();

		scoreText = new Text("Score");
		scoreText->GetTransform()->scale = { 2.f, 2.f };
		scoreText->GetTransform()->position = { 400.0f, (float)renderManager->WINDOW_HEIGHT + 70.0f };
		ui.push_back(scoreText);

		scoreNumberText = new Text("000000");
		scoreNumberText->GetTransform()->scale = { 2.f, 2.f };
		scoreNumberText->GetTransform()->position = { 400.0f, (float)renderManager->WINDOW_HEIGHT + 30.0f };
		ui.push_back(scoreNumberText);

		setScoreText = new Text("Enter Name: ");
		setScoreText->GetTransform()->scale = { 2.0f, 2.0f };
		setScoreText->GetTransform()->position = { renderManager->WINDOW_WIDTH / 2.0f, renderManager->WINDOW_HEIGHT / 2.0f };
		setScoreNameText = new Text(" ");
		setScoreNameText->GetTransform()->scale = { 2.0f, 2.0f };
		setScoreNameText->GetTransform()->position = { renderManager->WINDOW_WIDTH / 2.0f + 300.0f, renderManager->WINDOW_HEIGHT / 2.0f };

		player->SetLayer(20);
		spawnManager.SpawnObject(player);
	}

	void OnExit() override { Scene::OnExit(); }

	void OnUpdate() override {
		bool stateChanged = stateJustChanged;

		switch(state) {
			case GameplayState::GAMEPLAY:
			Scene::OnUpdate();

			if(inputManager->GetEvent(SDLK_ESCAPE, DOWN)) {
				SetPauseMenuVisibility(true);
				SetState(GameplayState::PAUSED);
			}

			if(player->IsDead()) {
				SetState(GameplayState::DEATH);
			}

			if(waveManager->IsCurrentWaveFinishedSpawning() &&
				!AreEnemiesRemaining()) {
				SetState(GameplayState::FINISH_STAGE);
			}

			break;

			case GameplayState::PAUSED:
			for(int i = ui.size() - 1; i >= 0; i--) {
				if(ui[i]->IsPendingDestroy()) {
					delete ui[i];
					ui.erase(ui.begin() + i);
				}
			}

			for(Object* u : ui) {
				u->Update();
			}

			if(inputManager->GetEvent(SDLK_ESCAPE, DOWN)) {
				SetPauseMenuVisibility(false);
				SetState(GameplayState::GAMEPLAY);
			}
			break;

			case GameplayState::FINISH_STAGE:
			if(waveManager->AreAllWavesFinishedSpawning()) {
				RecordHighScore();
			}
			else {
				//TODO: Finish Stage Transition
				waveManager->StartNextWave();
				SetState(GameplayState::GAMEPLAY);
			}
			break;

			case GameplayState::DEATH:
			if(stateJustChanged)
				timeManager->SubscribeEvent(
					std::make_pair(1.0f, [this]() { ShowDeathScreen(); })
				);
			break;
		}

		if(stateChanged) stateJustChanged = false;

		scoreNumberText->SetText(scoreManager->GetScoreAsText());
		if(scoreManager->IsHighScore()) {
			scoreText->SetColor({ 0xff, 0xd7, 0x00, 0xff });
		}
	}

	void Render() override { Scene::Render(); }

private:
	void SetPauseMenuVisibility(bool visible) {
		if(visible) {
			Button* resumeBtn = new Button([this]() {
				SetPauseMenuVisibility(false);
				SetState(GameplayState::GAMEPLAY);
			});
			resumeBtn->GetTransform()->position = { (float)renderManager->WINDOW_WIDTH / 2.0f, (float)renderManager->WINDOW_WIDTH / 2.0f };
			ui.push_back(resumeBtn);
		}
		else {
			ui.pop_back();
		}
	}

	void ShowDeathScreen() {
		Image* blackScreen = new Image("res/black-screen.png", Vector2(0, 0), Vector2((float)renderManager->WINDOW_WIDTH, (float)renderManager->WINDOW_HEIGHT));
		blackScreen->GetTransform()->position = { 0,0 };
		ui.push_back(blackScreen);
		timeManager->SubscribeEvent(std::make_pair(
			2.0f, [this]() { ui.pop_back(); ExitDeath(); }
		));
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
			waveManager->RestartWave();
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
			if(inputManager->GetEvent(key, DOWN)) {
				std::string name = setScoreNameText->GetText();
				char letter = key - SDLK_A + 'A';
				name += letter;
				setScoreNameText->SetText(name);
				break;
			}
		}
		if(inputManager->GetEvent(SDLK_RETURN, DOWN)) {
			//TODO: Hook up to file manager
			sceneManager->SetNextScene(SceneState::MENU);
		}

		for(int i = ui.size() - 1; i >= 0; i--) {
			if(ui[i]->IsPendingDestroy()) {
				delete ui[i];
				ui.erase(ui.begin() + i);
			}
		}

		for(Object* u : ui) {
			u->Update();
		}
	}
};