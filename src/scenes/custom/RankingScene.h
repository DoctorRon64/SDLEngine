#pragma once
#include "../Scene.h"
#include <Objects/Button.h>
#include <Objects/Text.h>
class RankingScene :
	public Scene {
public:
	RankingScene() = default;
	void OnEnter() override {
		std::vector<HighScore> highScores = ScoreManager::GetInstance()->GetScores();

		Image* bg = new Image(BLACK_SCREEN_SPRITE_PATH, { 0, 0 }, { 320, 200 });
		bg->GetTransform()->position = { 0,0 };
		bg->GetTransform()->scale = {
			(float)RenderManager::GetInstance()->WINDOW_WIDTH / 320.0f,
			(float)RenderManager::GetInstance()->WINDOW_HEIGHT / 200.0f };
		bg->SetLayer(20);
		ui.push_back(bg);

		Text* title = new Text("HIGH SCORES");
		title->GetTransform()->scale = { 2.f, 2.f };
		title->GetTransform()->position = { ((float)RenderManager::GetInstance()->WINDOW_WIDTH / 2) - 100, 0 };
		ui.push_back(title);

		float startX = 500.f;
		float startY = 100.0f;
		float spacing = 60.0f;

		for(int i = 0; i < highScores.size(); ++i) {
			std::string scoreAsText = ScoreManager::GetInstance()->MakeScoreAsText(highScores[i].score);
			std::string scoreName = highScores[i].name;
			Text* score = new Text(scoreName + " " + scoreAsText);
			score->GetTransform()->scale = { 2.f, 2.f };
			score->GetTransform()->position = { startX, startY + i * spacing };
			ui.push_back(score);
		}

		Text* returnLabel = new Text("Return");
		returnLabel->GetTransform()->scale = { 2.f, 2.f };

		Button* returnBtn = new Button([]() {
			SceneManager::GetInstance()->SetNextScene(SceneState::MENU);
		}, returnLabel);
		returnBtn->GetTransform()->position = {
			(float)RenderManager::GetInstance()->WINDOW_WIDTH / 2 - 150,
			(float)RenderManager::GetInstance()->WINDOW_HEIGHT - 150
		};
		ui.push_back(returnBtn);
		ui.push_back(returnLabel);
	}
};
