#pragma once
#include "../AnimatedImage.h"

class TestAnimation : public AnimatedImage {
public:
	TestAnimation() : AnimatedImage("res/man.png", { 0.f, 0.f }, { 95.f, 128.f }, 12, 3, 32.f, 32.f, true) {
		Vector2 randomPos = Vector2(rand() % RenderManager::GetInstance()->WINDOW_WIDTH, rand() % RenderManager::GetInstance()->WINDOW_HEIGHT);
		transform->position = randomPos;
		transform->scale = Vector2(.2f, .2f);
	}

	virtual void Update() override {
		Object::Update();
	}
};
