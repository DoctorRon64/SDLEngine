#pragma once
#include "objects/custom/baseEnemy.h"
#include "objects/custom/Player.h"
#include "scenes/Scene.h"
#include <objects/TextObject.h>

class GameplayScene : public Scene {
public:
	GameplayScene() = default;
	void OnEnter() override {
		renderManager->LoadTexture("res/evil-woman.png");
		spawnerManager.SpawnObject(new baseEnemy("res/evil-woman.png"));

		renderManager->LoadTexture("res/man.png");
		spawnerManager.SpawnObject(new Player("res/man.png"));

		auto text = new TextObject("Hola, chico bienvenido con el mejor juego!");
		text->GetTransform()->position = { 200.f, 200.f };
		ui.push_back(text);
	}

	void OnExit() override { Scene::OnExit(); }
	void OnUpdate() override { Scene::OnUpdate(); }
	void Render() override { Scene::Render(); }
};