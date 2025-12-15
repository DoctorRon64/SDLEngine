#pragma once
#include "objects/Button.h"
#include "scenes/Scene.h"
#include <objects/Text.h>

class MenuScene : public Scene {
public:
	MenuScene() = default;
	void OnEnter() override {
		Text* text = new Text("Menu / To continue press [Space] or [click] the { blue button }");
		text->GetTransform()->position = { 200.f, 200.f };
		ui.push_back(text);

		renderManager->LoadTexture("res/btn.png");
		auto texture = renderManager->GetTexture("res/btn.png");
		Button* btn = new Button([]() { sceneManager->SetNextScene(SceneState::GAMEPLAY); });
		ui.push_back(btn);
	}

	void OnExit() override {
		Scene::OnExit();
	}

	void OnUpdate() override {
		Scene::OnUpdate();

		if(inputManager->GetEvent(SDLK_SPACE, DOWN)) {
			std::cout << "something happend yeeess" << std::endl;
			sceneManager->SetNextScene(SceneState::GAMEPLAY);
		}
	}

	void Render() override {
		Scene::Render();
	}
};