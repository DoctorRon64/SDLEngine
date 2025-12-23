#pragma once
#include "objects/custom/Bullet.h"
#include "objects/custom/Enemy.h"
#include "objects/custom/Player.h"
#include "objects/custom/ScrollingBackground.h"
#include "scenes/Scene.h"
#include <objects/Enemies/BubbleEnemy.h>
#include <objects/Enemies/KillerWhaleEnemy.h>
#include <objects/Enemies/MedusaEnemy.h>
#include <objects/Text.h>
#include <wave/Wave.h>
#include <Objects/Button.h>

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
	Player* player = new Player();
	Text* scoreText;
	Text* scoreNumberText;

public:
	GameplayScene() = default;
	void OnEnter() override {
		ScrollingBackground* bg = new ScrollingBackground("res/bg.jpg", 200.0f, -1000);
		spawnerManager.SpawnObject(bg);

		Wave wave1;
		wave1.AddSpawn(0.0f, []() {
			spawnerManager.SpawnObject(new BubbleEnemy({ 1400.f, 200.f }));
		});
		wave1.AddSpawn(0.5f, []() {
			spawnerManager.SpawnObject(new MedusaEnemy({ 1400.f, 400.f }));
		});
		wave1.AddSpawn(0.5f, []() {
			spawnerManager.SpawnObject(new KillerWhaleEnemy({ 1400.f, 600.f }));
		});
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

		player->SetLayer(20);
		spawnerManager.SpawnObject(player);
	}

	void OnExit() override { Scene::OnExit(); }

	void OnUpdate() override {

		bool stateChanged = stateJustChanged;

		switch (state) {
		case GameplayState::GAMEPLAY:
			Scene::OnUpdate();

			if (inputManager->GetEvent(SDLK_ESCAPE, DOWN)) {
				SetPauseMenuVisibility(true);
				SetState(GameplayState::PAUSED);
			}

			if (player->IsDead()) {
				SetState(GameplayState::DEATH);
			}

			if (waveManager->IsCurrentWaveFinishedSpawning() &&
				!AreEnemiesRemaining()) {
				SetState(GameplayState::FINISH_STAGE);
			}

			break;

		case GameplayState::PAUSED:
			for (int i = ui.size() - 1; i >= 0; i--) {
				if (ui[i]->IsPendingDestroy()) {
					delete ui[i];
					ui.erase(ui.begin() + i);
				}
			}

			for (Object* u : ui) {
				u->Update();
			}

			if (inputManager->GetEvent(SDLK_ESCAPE, DOWN)) {
				SetPauseMenuVisibility(false);
				SetState(GameplayState::GAMEPLAY);
			}
			break;

		case GameplayState::FINISH_STAGE:
			if (waveManager->AreAllWavesFinishedSpawning()) {
				//TODO: Record hiscore
			}
			else {
				//TODO: Finish Stage Transition
				waveManager->StartNextWave();
				SetState(GameplayState::GAMEPLAY);
			}
			break;

		case GameplayState::DEATH:
			if (stateJustChanged) 
				timeManager->SubscribeEvent(
					std::make_pair(1.0f, [this](){ ShowDeathScreen(); })
				);
			break;
		}

		if (stateChanged) stateJustChanged = false;

		scoreNumberText->SetText(scoreManager->GetScoreAsText());
		if (scoreManager->IsHighScore()) {
			scoreText->SetColor({ 0xff, 0xd7, 0x00, 0xff });
		}

	}

	void Render() override { Scene::Render(); }

private:
	void SetPauseMenuVisibility(bool visible) {
		if (visible) {
			Button* resumeBtn = new Button([this]() {
				SetPauseMenuVisibility(false);
				SetState(GameplayState::GAMEPLAY);
				});
			resumeBtn->GetTransform()->position = { (float)renderManager->WINDOW_WIDTH / 2.0f, (float)renderManager->WINDOW_WIDTH / 2.0f };
			ui.push_back(resumeBtn);
		}
		else {
			ui.back()->Destroy();
		}
	}

	void ShowDeathScreen() {
		Image* blackScreen = new Image("res/black-screen.png", Vector2(0, 0), Vector2((float)renderManager->WINDOW_WIDTH, (float)renderManager->WINDOW_HEIGHT));
		blackScreen->GetTransform()->position = { 0,0 };
		ui.push_back(blackScreen);
		timeManager->SubscribeEvent(std::make_pair(
			2.0f, [this]() { ExitDeath(); }
		));
	}

	void ExitDeath() {
		ui.back()->Destroy();
		if (player->GetLives() > 0) {
			player->DecrementLives(1);
			player->HealToMax();
			player->GetTransform()->position = { 0, 0 };
			for (int i = 0; i < objects.size(); ++i) {
				Enemy* enemy;
				if (enemy = dynamic_cast<Enemy*>(objects[i])) {
					objects[i]->Destroy();
				}
			}
			waveManager->RestartWave();
			this->SetState(GameplayState::GAMEPLAY);
		}
		else {
			//TODO: Record hiscore
		}
	}

	void SetState(GameplayState _state) {
		state = _state;
		stateJustChanged = true;
	}

	bool AreEnemiesRemaining() {
		for (Object* obj : objects) {
			Enemy* enemy; 
			if (enemy = dynamic_cast<Enemy*>(obj)) return true;
		}
		return false;
	}

};