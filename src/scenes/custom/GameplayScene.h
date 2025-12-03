#pragma once
#include "objects/custom/background.h"
#include "objects/custom/baseEnemy.h"
#include "objects/custom/bullet.h"
#include "objects/custom/Player.h"
#include "scenes/Scene.h"
#include <objects/TextObject.h>

class GameplayScene : public Scene {
public:
	GameplayScene() = default;
	void OnEnter() override {
		const std::string bgTexture = "res/bg.jpg";
		renderManager->LoadTexture(bgTexture);
		auto bg = new background(bgTexture);
		bg->SetLayer(-999);
		spawnerManager.SpawnObject(bg);
		objects.push_back(bg);

		const std::string enemyTexture = "res/evil-woman.png";
		renderManager->LoadTexture(enemyTexture);
		auto enemy = new baseEnemy(enemyTexture);
		enemy->SetLayer(10);
		spawnerManager.SpawnObject(enemy);
		objects.push_back(enemy);

		const std::string playerTexture = "res/man.png";
		renderManager->LoadTexture(playerTexture);
		auto player = new Player(playerTexture);
		player->SetLayer(20);
		spawnerManager.SpawnObject(player);
		objects.push_back(player);

		auto text = new TextObject("Hola, chico bienvenido con el mejor juego!");
		text->GetTransform()->position = { 200.f, 200.f };
		ui.push_back(text);
	}

	void OnExit() override { Scene::OnExit(); }
	void OnUpdate() override { Scene::OnUpdate(); }
	void Render() override { Scene::Render(); }
};