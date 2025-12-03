#pragma once
#include "scenes/Scene.h"
#include <objects/TextObject.h>

class MenuScene : public Scene {
public:
	MenuScene() = default;
	void OnEnter() override {
		TextObject* text = new TextObject("Menu");
		text->GetTransform()->position = { 200.f, 200.f };
		ui.push_back(text);
	}

	void OnExit() override { Scene::OnExit(); }
	void OnUpdate() override {
		Scene::OnUpdate();

		if(inputManager->GetEvent(SDLK_SPACE, DOWN)) {
			std::cout << "something happend yeeess" << std::endl;
			sceneManager->SetNextScene(GAMEPLAY);
		}
	}
	void Render() override { Scene::Render(); }
};