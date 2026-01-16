#pragma once
#include "../Image.h"

class ScrollingBackground : public Object {
public:
	ScrollingBackground(const std::string& texturePath, float speed, int layer = -1000) : scrollSpeed(speed) {
		bgA = new Image(texturePath, { 0, 0 }, { WIDTH, HEIGHT });
		bgB = new Image(texturePath, { 0, 0 }, { WIDTH, HEIGHT });

		bgA->SetLayer(layer);
		bgB->SetLayer(layer);

		Vector2 texSize = bgA->GetTransform()->GetSize();
		width = texSize.x;
		height = texSize.y;

		bgA->GetTransform()->position = { 0, 0 };
		bgB->GetTransform()->position = { width, 0 };

		SpawnManager::Instance().SpawnObject(bgA);
		std::cout << bgA->GetTransform()->position.x << ", " << bgA->GetTransform()->position.y << std::endl;

		SpawnManager::Instance().SpawnObject(bgB);
	}

	~ScrollingBackground() = default;
	void Render() override {}

	virtual void Update() override {
		float dt = TimeManager::GetInstance()->GetDeltaTime();

		bgA->GetTransform()->position.x -= scrollSpeed * dt;
		bgB->GetTransform()->position.x -= scrollSpeed * dt;

		Wrap(bgA, bgB);
		Wrap(bgB, bgA);
	}

private:
	void Wrap(Image* current, Image* other) {
		if(current->GetTransform()->position.x <= -width) {
			current->GetTransform()->position.x = other->GetTransform()->position.x + width;
		}
	}

private:
	Image* bgA = nullptr;
	Image* bgB = nullptr;

	float scrollSpeed = 100.f;
	float width = 0.f;
	float height = 0.f;
};
