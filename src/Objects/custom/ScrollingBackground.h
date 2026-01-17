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
		SyncImage(bgA);
		SyncImage(bgB);

		SpawnManager::Instance().SpawnObject(bgA);
		std::cout << bgA->GetTransform()->position.x << ", " << bgA->GetTransform()->position.y << std::endl;

		SpawnManager::Instance().SpawnObject(bgB);
	}

	~ScrollingBackground() = default;
	void Render() override {}

	void Reset() {
		if(!bgA || !bgB) return;
		bgA->GetTransform()->position = { 0, 0 };
		bgB->GetTransform()->position = { width, 0 };
		SyncImage(bgA);
		SyncImage(bgB);
	}

	virtual void Update() override {
		float dt = TimeManager::GetInstance()->GetDeltaTime();

		bgA->GetTransform()->position.x -= scrollSpeed * dt;
		bgB->GetTransform()->position.x -= scrollSpeed * dt;

		Wrap(bgA, bgB);
		Wrap(bgB, bgA);

		SyncImage(bgA);
		SyncImage(bgB);
	}

private:
	void Wrap(Image* current, Image* other) {
		if(current->GetTransform()->position.x <= -width) {
			current->GetTransform()->position.x = other->GetTransform()->position.x + width;
		}
	}

	void SyncImage(Image* image) {
		if(!image) return;
		Renderer* renderer = image->GetRenderer();
		if(!renderer) return;
		Vector2 size = image->GetTransform()->GetSize();
		renderer->SetDestinationRect({
			static_cast<float>(image->GetTransform()->position.x),
			static_cast<float>(image->GetTransform()->position.y),
			static_cast<float>(size.x),
			static_cast<float>(size.y)
		});
	}

private:
	Image* bgA = nullptr;
	Image* bgB = nullptr;

	float scrollSpeed = 100.f;
	float width = 0.f;
	float height = 0.f;
};
