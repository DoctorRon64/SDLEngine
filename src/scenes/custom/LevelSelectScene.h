#pragma once
#include "../Scene.h"
#include "GameplayScene.h"
#include <Objects/Text.h>
#include <Objects/Button.h>
#include <Utils/config.h>
class LevelSelectScene :
	public Scene {
public:
	LevelSelectScene() = default;
	void OnEnter() override {
		AudioManager::GetInstance()->PlaySoundLooping(MUSIC_MENACE_SUBTUNE_2_PATH);

		Text* title = new Text("[LEVEL SELECT]");
		title->GetTransform()->scale = { 2.f, 2.f };
		title->GetTransform()->position = { ((float)RenderManager::GetInstance()->WINDOW_WIDTH / 2) - 300, 0 };
		ui.push_back(title);

		float startX = 500.f;
		float startY = 180.0f;
		float spacing = 130.0f;

		for(int i = 0; i < LEVEL_COUNT; ++i) {
			Text* levelLabel = new Text("Level " + std::to_string(i + 1));
			levelLabel->GetTransform()->scale = { 2.f, 2.f };

			Button* levelBtn = new Button([i]() {
				dynamic_cast<GameplayScene*>(SceneManager::GetInstance()->GetScene(SceneState::GAMEPLAY))->SetLevel(i);
				SceneManager::GetInstance()->SetNextScene(SceneState::GAMEPLAY);
			}, levelLabel);
			levelBtn->GetTransform()->position = { startX, startY + i * spacing };
			ui.push_back(levelBtn);
			ui.push_back(levelLabel);
		}

		//======================================================

		Text* menuLabel = new Text("Main Menu");
		menuLabel->GetTransform()->scale = { 2.f, 2.f };

		Button* menuBtn = new Button([]() {
			SceneManager::GetInstance()->SetNextScene(SceneState::MENU);
		}, menuLabel);
		menuBtn->GetTransform()->position = { startX, startY + spacing * 3 };
		ui.push_back(menuBtn);
		ui.push_back(menuLabel);
	}
};
