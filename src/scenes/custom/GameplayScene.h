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

public:
	GameplayScene() = default;
	void OnEnter() override {
		auto bg = new ScrollingBackground("res/bg.jpg", 200.0f, -1000);
		spawnerManager.SpawnObject(bg);

		Wave wave1;
		wave1.AddSpawn(0.0f, []() {
			return new BubbleEnemy({ 1400.f, 200.f });
		});
		wave1.AddSpawn(0.5f, []() {
			return new MedusaEnemy({ 1400.f, 400.f });
		});
		wave1.AddSpawn(0.5f, []() {
			return new KillerWhaleEnemy({ 1400.f, 600.f });
		});
		waveManager->AddWave(std::move(wave1));
		waveManager->Start();

		player->SetLayer(20);
		spawnerManager.SpawnObject(player);
	}

	void OnExit() override { Scene::OnExit(); }

	void OnUpdate() override {

		bool stateChanged = stateJustChanged;

		switch (state) {
		case GameplayState::GAMEPLAY:
			waveManager->Update();
			Scene::OnUpdate();

			if (inputManager->GetEvent(SDLK_ESCAPE, DOWN)) {
				SetPauseMenuVisibility(true);
				setState(GameplayState::PAUSED);
			}

			if (player->isDead()) {
				setState(GameplayState::DEATH);
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
				setState(GameplayState::GAMEPLAY);
			}
			break;

		case GameplayState::FINISH_STAGE:
			//TODO: Finish Stage
			break;

		case GameplayState::DEATH:
			if (stateJustChanged) 
				timeManager->SubscribeEvent(
					std::make_pair(1.0f, [this](){ ShowDeathScreen(); })
				);
			break;
		}

		if (stateChanged) stateJustChanged = false;

	}

	void Render() override { Scene::Render(); }

private:
	void SetPauseMenuVisibility(bool visible) {
		if (visible) {
			Button* resumeBtn = new Button([this]() {
				SetPauseMenuVisibility(false);
				setState(GameplayState::GAMEPLAY);
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
			2.0f, [this]() { ExitDeath(); }
		));
	}

	void ExitDeath() {
		ui.pop_back();
		if (player->GetLives() > 0) {
			player->DecrementLives(1);
			player->HealToMax();
			player->GetTransform()->position = { 0, 0 };
			OnExit();
			OnEnter();
		}
		else {
			//TODO: Record hiscore
		}
	}

	void setState(GameplayState _state) {
		state = _state;
		stateJustChanged = true;
	}

};