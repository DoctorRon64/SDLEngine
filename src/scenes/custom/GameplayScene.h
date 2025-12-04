#pragma once
#include "objects/custom/background.h"
#include "objects/custom/baseEnemy.h"
#include "objects/custom/bullet.h"
#include "objects/custom/Player.h"
#include "scenes/Scene.h"
#include <objects/Text.h>

class GameplayScene : public Scene {
public:
	GameplayScene() = default;
	void OnEnter() override {
		renderManager->LoadTexture("res/bg.jpg");
		auto bg = new background();
		bg->SetLayer(-999);
		spawnerManager.SpawnObject(bg);
		objects.push_back(bg);

		renderManager->LoadTexture("res/evil-woman.png");
		auto enemy = new baseEnemy();
		enemy->SetLayer(10);
		spawnerManager.SpawnObject(enemy);
		objects.push_back(enemy);

		renderManager->LoadTexture("res/man.png");
		auto player = new Player();
		player->SetLayer(20);
		spawnerManager.SpawnObject(player);
		objects.push_back(player);

		auto text = new Text("Hola, chico bienvenido con el mejor juego!");
		text->GetTransform()->position = { 200.f, 200.f };
		ui.push_back(text);
	}

	void OnExit() override { Scene::OnExit(); }
	void OnUpdate() override { Scene::OnUpdate(); }
	void Render() override { Scene::Render(); }
};