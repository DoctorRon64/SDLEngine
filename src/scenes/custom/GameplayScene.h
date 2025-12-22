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

		auto player = new Player();
		player->SetLayer(20);
		spawnerManager.SpawnObject(player);
	}

	void OnExit() override { Scene::OnExit(); }
	void OnUpdate() override {
		waveManager->Update();
		Scene::OnUpdate();
	}

	void Render() override { Scene::Render(); }
};