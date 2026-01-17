#pragma once
#include "objects/Button.h"
#include "scenes/Scene.h"
#include <objects/Text.h>

class MenuScene : public Scene {
public:
	MenuScene() = default;
	void OnEnter() override {
		SDL_Color uiColor = { 0x00, 0x00, 0x00, 0xff };

		Image* bg = new Image(MENU_SCREEN_PATH, { 0, 0 }, { (float)RenderManager::GetInstance()->WINDOW_WIDTH, (float)RenderManager::GetInstance()->WINDOW_HEIGHT });
		bg->GetTransform()->position = { 0,0 };
		bg->SetLayer(20);
		ui.push_back(bg);

		AudioManager::GetInstance()->PlaySoundLooping(MUSIC_MENACE_TITLE_PATH);

		Text* title = new Text("[MENACE ARCADE GAME]", { 0xff, 0xff, 0xff, 0xff });
		title->GetTransform()->scale = { 2.f, 2.f };
		title->GetTransform()->position = { ((float)RenderManager::GetInstance()->WINDOW_WIDTH / 2) - 300, 30 };
		ui.push_back(title);

		const Vector2 buttonSize = { 220.f, 60.f };
		float startX = (float)RenderManager::GetInstance()->WINDOW_WIDTH * 0.5f - buttonSize.x * 0.5f;
		float startY = 220.0f;
		float spacing = 80.0f;

		Text* playLabel = new Text("Play", uiColor);
		playLabel->GetTransform()->scale = { 1.f, 1.f };

		Button* playBtn = new Button([]() {
			SceneManager::GetInstance()->SetNextScene(SceneState::LEVEL_SELECT);
		}, playLabel, buttonSize);
		playBtn->GetTransform()->position = { startX, startY };
		ui.push_back(playBtn);
		ui.push_back(playLabel);

		//======================================================

		Text* rankingLabel = new Text("Ranking", uiColor);
		rankingLabel->GetTransform()->scale = { 1.f, 1.f };

		Button* rankingBtn = new Button([]() {
			SceneManager::GetInstance()->SetNextScene(SceneState::RANKING);
		}, rankingLabel, buttonSize);
		rankingBtn->GetTransform()->position = { startX, startY + spacing };
		ui.push_back(rankingBtn);
		ui.push_back(rankingLabel);

		//=====================================================

		Text* audioLabel = new Text("Audio", uiColor);
		audioLabel->GetTransform()->scale = { 1.f, 1.f };

		Button* audioBtn = new Button([]() {
			static bool muted = false;
			muted = !muted;

			if(muted)
				AudioManager::GetInstance()->Mute();
			else
				AudioManager::GetInstance()->Unmute();
		}, audioLabel, buttonSize);
		audioBtn->GetTransform()->position = { startX, startY + spacing * 2 };
		ui.push_back(audioBtn);
		ui.push_back(audioLabel);

		//======================================================

		Text* exitLabel = new Text("Exit", uiColor);
		exitLabel->GetTransform()->scale = { 1.f, 1.f };

		Button* exitBtn = new Button([]() {
			SDL_Event quit{};
			quit.type = SDL_EVENT_QUIT;
			SDL_PushEvent(&quit);
		}, exitLabel, buttonSize);
		exitBtn->GetTransform()->position = { startX, startY + spacing * 3 };
		ui.push_back(exitBtn);
		ui.push_back(exitLabel);
	}

	void OnExit() override {
		Scene::OnExit();
	}

	void OnUpdate() override {
		Scene::OnUpdate();
	}

	void Render() override {
		Scene::Render();
	}
};
