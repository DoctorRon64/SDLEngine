#pragma once
#include "../Scene.h"
#include <Objects/Button.h>
#include <Objects/Text.h>
class RankingScene :
	public Scene {
public:
	RankingScene() = default;
	void OnEnter() override {
		ScoreManager::GetInstance()->Init();
		std::vector<HighScore> highScores = ScoreManager::GetInstance()->GetScores();

		SDL_Color uiColor = { 0x00, 0x00, 0x00, 0xff };

		Image* bg = new Image(RANKING_SCREEN_PATH, { 0, 0 }, { (float)RenderManager::GetInstance()->WINDOW_WIDTH, (float)RenderManager::GetInstance()->WINDOW_HEIGHT });
		bg->GetTransform()->position = { 0,0 };
		bg->SetLayer(20);
		ui.push_back(bg);

		const Vector2 panelTextureSize = { 700.f, 480.f };
		const Vector2 panelSize = { 640.f, 420.f };
		Image* panel = new Image(RANKING_PANEL_PATH, { 0, 0 }, panelTextureSize);
		panel->GetTransform()->scale = { panelSize.x / panelTextureSize.x, panelSize.y / panelTextureSize.y };
		panel->GetTransform()->position = {
			(float)RenderManager::GetInstance()->WINDOW_WIDTH * 0.5f - panelSize.x * 0.5f,
			110.0f
		};
		ui.push_back(panel);

		Text* title = new Text("HIGH SCORES", { 0xff, 0xff, 0xff, 0xff });
		title->GetTransform()->scale = { 2.f, 2.f };
		title->GetTransform()->position = { ((float)RenderManager::GetInstance()->WINDOW_WIDTH / 2) - 180, 40 };
		ui.push_back(title);

		float panelLeft = panel->GetTransform()->position.x - 40;
		float panelTop = panel->GetTransform()->position.y;
		float startY = panelTop + 70.0f;
		float spacing = 36.0f;
		float nameX = panelLeft + 70.0f;
		float scoreX = panelLeft + panelSize.x - 210.0f;

		Text* nameHeader = new Text("NAME", uiColor);
		nameHeader->GetTransform()->scale = { 1.4f, 1.4f };
		nameHeader->GetTransform()->position = { nameX, panelTop + 30.0f };
		ui.push_back(nameHeader);

		Text* scoreHeader = new Text("SCORE", uiColor);
		scoreHeader->GetTransform()->scale = { 1.4f, 1.4f };
		scoreHeader->GetTransform()->position = { scoreX, panelTop + 30.0f };
		ui.push_back(scoreHeader);

		auto toName = [](const HighScore& entry) {
			std::string name;
			for(int i = 0; i < MAX_USER_LENGTH; ++i) {
				if(entry.name[i] == '\0') break;
				name += entry.name[i];
			}
			if(name.empty()) name = "-----";
			return name;
		};

		if(highScores.empty()) {
			Text* emptyText = new Text("NO SCORES YET", uiColor);
			emptyText->GetTransform()->scale = { 1.5f, 1.5f };
			emptyText->GetTransform()->position = { panelLeft + 180.0f, panelTop + 200.0f };
			ui.push_back(emptyText);
		}

		for(int i = 0; i < highScores.size() && i < MAX_STORED_SCORES; ++i) {
			std::string scoreAsText = ScoreManager::GetInstance()->MakeScoreAsText(highScores[i].score);
			std::string scoreName = toName(highScores[i]);

			Text* nameText = new Text(scoreName, uiColor);
			nameText->GetTransform()->scale = { 1.3f, 1.3f };
			nameText->GetTransform()->position = { nameX, startY + i * spacing };
			ui.push_back(nameText);

			Text* scoreText = new Text(scoreAsText, uiColor);
			scoreText->GetTransform()->scale = { 1.3f, 1.3f };
			scoreText->GetTransform()->position = { scoreX, startY + i * spacing };
			ui.push_back(scoreText);
		}

		const Vector2 buttonSize = { 220.f, 60.f };
		Text* returnLabel = new Text("Return", uiColor);
		returnLabel->GetTransform()->scale = { 1.f, 1.f };

		Button* returnBtn = new Button([]() {
			SceneManager::GetInstance()->SetNextScene(SceneState::MENU);
		}, returnLabel, buttonSize);
		returnBtn->GetTransform()->position = {
			(float)RenderManager::GetInstance()->WINDOW_WIDTH * 0.5f - buttonSize.x * 0.5f,
			panelTop + panelSize.y + 30.0f
		};
		ui.push_back(returnBtn);
		ui.push_back(returnLabel);
	}
};
