#pragma once
#include "../AnimatedImage.h"

class TestAnimation : public AnimatedImage {
public:
	TestAnimation() : AnimatedImage("res/man.png", { 0.f, 0.f }, { 95.f, 128.f }, 12, 3, 32.f, 32.f, 1, true) {
		Vector2 randomPos = Vector2(RenderManager::GetInstance()->WINDOW_WIDTH / 2, RenderManager::GetInstance()->WINDOW_HEIGHT / 2);
		transform->position = randomPos;
		transform->scale = Vector2(.2f, .2f);
	}

	virtual void Update() override {
		Object::Update();
	}
};
