#pragma once
#include "objects/custom/background.h"
#include "objects/custom/baseEnemy.h"
#include "objects/custom/Player.h"
#include "scenes/Scene.h"
#include <objects/TextObject.h>

class GameplayScene : public Scene {
public:
	GameplayScene() = default;
	void OnEnter() override {
		const std::string bgTexture = "res/bg.jpg";
		renderManager->LoadTexture(bgTexture);
		auto bg = new background(bgTexture, Vector2(0, 0), Vector2(1175, 700), Vector2(20.f, 20.f));
		bg->SetLayer(-999);
		spawnerManager.SpawnObject(bg);

		const std::string enemyTexture = "res/evil-woman.png";
		renderManager->LoadTexture(enemyTexture);
		auto enemy = new baseEnemy(enemyTexture);
		enemy->SetLayer(10);
		spawnerManager.SpawnObject(enemy);

		const std::string playerTexture = "res/man.png";
		renderManager->LoadTexture(playerTexture);
		renderManager->LoadTexture("res/bullet.png");
		auto player = new Player(playerTexture);
		player->SetLayer(20);
		spawnerManager.SpawnObject(player);

		auto text = new TextObject("Hola, chico bienvenido con el mejor juego!");
		text->GetTransform()->position = { 200.f, 200.f };
		ui.push_back(text);
	}

	void OnExit() override { Scene::OnExit(); }
	void OnUpdate() override { Scene::OnUpdate(); }
	void Render() override { Scene::Render(); }
};