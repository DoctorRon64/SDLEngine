#pragma once
#include "ImageObject.h"
#include "Managers/RenderManager.h"

class TestObject : public ImageObject {
public:
	TestObject() : ImageObject("res/ship.jpg", Vector2(0.f, 0.f), Vector2(306.f, 562.f)) {
		Vector2 randomPosition = Vector2(
			static_cast<float>(rand() % renderManager->WINDOW_WIDTH),
			static_cast<float>(rand() % renderManager->WINDOW_HEIGHT)
		);
		transform->position = randomPosition;
		transform->scales = Vector2(0.5f, 0.5f);
		transform->rotation = 30.f;
		transform->size = Vector2(306.f, 562.f);
	}
};