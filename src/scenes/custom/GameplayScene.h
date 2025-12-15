#pragma once
#include "objects/custom/background.h"
#include "objects/custom/Bullet.h"
#include "objects/custom/Enemy.h"
#include "objects/custom/Player.h"
#include "scenes/Scene.h"
#include <objects/Text.h>

enum class GameplayState {
	GAMEPLAY,
	PAUSED,
	FINISH_STAGE,
	DEATH
};

class GameplayScene : public Scene {
private:
	GameplayState state = GameplayState::GAMEPLAY;

public:
	GameplayScene() = default;
	void OnEnter() override {
		auto bg = new Background();
		bg->SetLayer(-999);
		spawnerManager.SpawnObject(bg);

		auto enemy = new Enemy();
		enemy->SetLayer(10);
		spawnerManager.SpawnObject(enemy);

		auto player = new Player();
		player->SetLayer(20);
		spawnerManager.SpawnObject(player);

		auto text = new Text("Hola, chico bienvenido con el mejor juego!");
		text->GetTransform()->position = { 200.f, 200.f };
		ui.push_back(text);
	}

	void OnExit() override { Scene::OnExit(); }
	void OnUpdate() override {
		switch(state) {
			case GameplayState::GAMEPLAY:
			Scene::OnUpdate();
			break;
			case GameplayState::PAUSED:
			//UpdatePause();
			break;
			case GameplayState::FINISH_STAGE:
			//UpdateFinishStage();
			break;
			case GameplayState::DEATH:
			//UpdateDeath();
			break;
		}
	}

	void Render() override { Scene::Render(); }
};