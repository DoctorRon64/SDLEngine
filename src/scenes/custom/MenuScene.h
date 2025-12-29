#pragma once
#include "objects/Button.h"
#include "scenes/Scene.h"
#include <objects/Text.h>

class MenuScene : public Scene {
public:
	MenuScene() = default;
	void OnEnter() override {
		AudioManager::GetInstance()->PlaySoundLooping("res/audio/music/menace_title.wav");

		Text* title = new Text("[MENACE ARCADE GAME]");
		title->GetTransform()->scale = { 2.f, 2.f };
		title->GetTransform()->position = { ((float)RenderManager::GetInstance()->WINDOW_WIDTH / 2) - 300, 0 };
		ui.push_back(title);

		float startX = 500.f;
		float startY = 180.0f;
		float spacing = 130.0f;

		Text* playLabel = new Text("Play");
		playLabel->GetTransform()->scale = { 2.f, 2.f };
		
		Button* playBtn = new Button([]() {
			SceneManager::GetInstance()->SetNextScene(SceneState::GAMEPLAY);
		}, playLabel);
		playBtn->GetTransform()->position = { startX, startY };
		ui.push_back(playBtn);
		ui.push_back(playLabel);

		//======================================================

		Text* rankingLabel = new Text("Ranking");
		rankingLabel->GetTransform()->scale = { 2.f, 2.f };

		Button* rankingBtn = new Button([]() {
			SceneManager::GetInstance()->SetNextScene(SceneState::RANKING);
		}, rankingLabel);
		rankingBtn->GetTransform()->position = { startX, startY + spacing };
		ui.push_back(rankingBtn);
		ui.push_back(rankingLabel);

		//=====================================================

		Text* audioLabel = new Text("Audio");
		audioLabel->GetTransform()->scale = { 2.f, 2.f };

		Button* audioBtn = new Button([]() {
			static bool muted = false;
			muted = !muted;

			if(muted)
				AudioManager::GetInstance()->Mute();
			else
				AudioManager::GetInstance()->Unmute();
		}, audioLabel);
		audioBtn->GetTransform()->position = { startX, startY + spacing * 2 };
		ui.push_back(audioBtn);
		ui.push_back(audioLabel);

		//======================================================

		Text* exitLabel = new Text("Exit");
		exitLabel->GetTransform()->scale = { 2.f, 2.f };

		Button* exitBtn = new Button([]() {
			SDL_Event quit{};
			quit.type = SDL_EVENT_QUIT;
			SDL_PushEvent(&quit);
		}, exitLabel);
		exitBtn->GetTransform()->position = { startX, startY + spacing * 3 };
		ui.push_back(exitBtn);
		ui.push_back(exitLabel);
	}

	void OnExit() override {
		Scene::OnExit();
	}

	void OnUpdate() override {
		Scene::OnUpdate();

		if(InputManager::GetInstance()->GetEvent(SDLK_SPACE, DOWN)) {
			std::cout << "something happend yeeess" << std::endl;
			SceneManager::GetInstance()->SetNextScene(SceneState::GAMEPLAY);
		}
	}

	void Render() override {
		Scene::Render();
	}
};