#pragma once
#include "../Image.h"

class Background : public Object {
private:
	float scrollSpeed = 200.0f;
	float width;

	Image* bg1;
	Image* bg2;

public:
	Background(const std::string& path = "res/bg.jpg") {
		float textureWidth = 1175.f;
		float textureHeight = 700.f;
		float scale = 10.f;

		bg1 = new Image(path, { 0, 0 }, { textureWidth, textureHeight });
		bg2 = new Image(path, { 0, 0 }, { textureWidth, textureHeight });

		bg1->GetTransform()->scale = { scale, scale };
		bg2->GetTransform()->scale = { scale, scale };

		bg1->GetTransform()->position = { 0.f, 0.f };
		bg2->GetTransform()->position = { textureWidth, 0.f };

		bg1->SetLayer(-1000);
		bg2->SetLayer(-999);

		width = textureWidth * scale;

		spawnerManager.SpawnObject(bg1);
		spawnerManager.SpawnObject(bg2);
	}

	void Update() override {
		float deltaTime = timeManager->GetDeltaTime();

		bg1->GetTransform()->position.x -= scrollSpeed * deltaTime;
		bg2->GetTransform()->position.x -= scrollSpeed * deltaTime;

		if(bg1->GetTransform()->position.x <= -width) {
			bg1->GetTransform()->position.x = bg2->GetTransform()->position.x + width;
		}

		if(bg2->GetTransform()->position.x <= -width) {
			bg2->GetTransform()->position.x = bg1->GetTransform()->position.x + width;
		}
	}

	virtual void Render() override {
		bg1->Render();
		bg2->Render();
	}
};
