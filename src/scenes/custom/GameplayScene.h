#pragma once
#include "Objects/TestObject.h"
#include "scenes/Scene.h"
#include <objects/TextObject.h>

class GameplayScene : public Scene {
public:
	GameplayScene() = default;
	void OnEnter() override {
		spawnerManager.SpawnObject(new TestObject());

		TextObject* text = new TextObject("¡Hola, chico bienvenido con el mejor juego!");

		text->GetTransform()->position = { 200.f, 200.f };
		ui.push_back(text);
	}

	void OnExit() override { Scene::OnExit(); }
	void OnUpdate() override { Scene::OnUpdate(); }
	void Render() override { Scene::Render(); }
};