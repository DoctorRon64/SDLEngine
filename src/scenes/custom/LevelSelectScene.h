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
		SDL_Color uiColor = { 0x00, 0x00, 0x00, 0xff };

		Image* bg = new Image(LEVEL_SELECT_SCREEN_PATH, { 0, 0 }, { (float)RenderManager::GetInstance()->WINDOW_WIDTH, (float)RenderManager::GetInstance()->WINDOW_HEIGHT });
		bg->GetTransform()->position = { 0,0 };
		bg->SetLayer(20);
		ui.push_back(bg);

		AudioManager::GetInstance()->PlaySoundLooping(MUSIC_MENACE_SUBTUNE_2_PATH);

		Text* title = new Text("[LEVEL SELECT]", { 0xff, 0xff, 0xff, 0xff });
		title->GetTransform()->scale = { 2.f, 2.f };
		title->GetTransform()->position = { ((float)RenderManager::GetInstance()->WINDOW_WIDTH / 2) - 200, 30 };
		ui.push_back(title);

		const Vector2 buttonSize = { 220.f, 60.f };
		float startX = (float)RenderManager::GetInstance()->WINDOW_WIDTH * 0.5f - buttonSize.x * 0.5f;
		float startY = 220.0f;
		float spacing = 80.0f;

		for(int i = 0; i < LEVEL_COUNT; ++i) {
			Text* levelLabel = new Text("Level " + std::to_string(i + 1), uiColor);
			levelLabel->GetTransform()->scale = { 1.f, 1.f };

			Button* levelBtn = new Button([i]() {
				dynamic_cast<GameplayScene*>(SceneManager::GetInstance()->GetScene(SceneState::GAMEPLAY))->SetLevel(i);
				SceneManager::GetInstance()->SetNextScene(SceneState::GAMEPLAY);
			}, levelLabel, buttonSize);
			levelBtn->GetTransform()->position = { startX, startY + i * spacing };
			ui.push_back(levelBtn);
			ui.push_back(levelLabel);
		}

		//======================================================

		Text* menuLabel = new Text("Main Menu", uiColor);
		menuLabel->GetTransform()->scale = { 1.f, 1.f };

		Button* menuBtn = new Button([]() {
			SceneManager::GetInstance()->SetNextScene(SceneState::MENU);
		}, menuLabel, buttonSize);
		menuBtn->GetTransform()->position = { startX, startY + spacing * LEVEL_COUNT };
		ui.push_back(menuBtn);
		ui.push_back(menuLabel);
	}
};
