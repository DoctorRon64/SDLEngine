#pragma once
#include "objects/Button.h"
#include "scenes/Scene.h"
#include <objects/Text.h>

class MenuScene : public Scene {
public:
	MenuScene() = default;
	void OnEnter() override {
		audioManager->PlaySoundLooping("res/audio/music/menace_title.wav");

		Text* title = new Text("[MENACE ARCADE GAME]");
		title->GetTransform()->scale = { 2.f, 2.f };
		title->GetTransform()->position = { ((float)renderManager->WINDOW_WIDTH / 2) - 300, 200.f };
		ui.push_back(title);

		float startX = 500.f;
		float startY = 250.f;
		float spacing = 90.f;

		Button* playBtn = new Button([]() {
			sceneManager->SetNextScene(SceneState::GAMEPLAY);
		});
		playBtn->GetTransform()->position = { startX, startY };
		ui.push_back(playBtn);

		//======================================================

		Button* rankingBtn = new Button([]() {
			sceneManager->SetNextScene(SceneState::RANKING);
		});
		rankingBtn->GetTransform()->position = { startX, startY + spacing };
		ui.push_back(rankingBtn);

		//=====================================================
		Button* audioBtn = new Button([]() {
			static bool muted = false;
			muted = !muted;

			if(muted)
				audioManager->Mute();
			else
				audioManager->Unmute();
		});
		audioBtn->GetTransform()->position = { startX, startY + spacing * 2 };
		ui.push_back(audioBtn);

		//======================================================
		Button* exitBtn = new Button([]() {
			SDL_Event quit{};
			quit.type = SDL_EVENT_QUIT;
			SDL_PushEvent(&quit);
		});
		exitBtn->GetTransform()->position = { startX, startY + spacing * 3 };
		ui.push_back(exitBtn);
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