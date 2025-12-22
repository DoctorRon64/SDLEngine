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

		switch (state) {
		case GameplayState::GAMEPLAY:
			waveManager->Update();
			Scene::OnUpdate();

			if (inputManager->GetEvent(SDLK_ESCAPE, DOWN)) {
				SetPauseMenuVisibility(true);
				state = GameplayState::PAUSED;
			}

			if (player->isDead()) {
				state = GameplayState::DEATH;
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
				state = GameplayState::GAMEPLAY;
			}
			break;

		case GameplayState::FINISH_STAGE:
			//TODO: Finish Stage
			break;

		case GameplayState::DEATH:
			//TODO: Death
			break;
		}
	}

	void Render() override { Scene::Render(); }

	void SetPauseMenuVisibility(bool visible) {
		if (visible) {
			Button* resumeBtn = new Button([this]() {
				SetPauseMenuVisibility(false);
				state = GameplayState::GAMEPLAY;
				});
			resumeBtn->GetTransform()->position = { renderManager->WINDOW_WIDTH / 2, renderManager->WINDOW_WIDTH / 2 };
			ui.push_back(resumeBtn);
		}
		else {
			ui.pop_back();
		}
	}

};