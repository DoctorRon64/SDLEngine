#pragma once
#include "../Image.h"

class background : public Image {
private:
	float scrollSpeed = 200.0f;

public:
	background(std::string _name = "res/bg.jpg",
		Vector2 _pos = Vector2(0.f, 0.f),
		Vector2 _size = Vector2(1024.f, 1303.f),
		Vector2 _scale = Vector2(10.0f, 13.0f))
		: Image(_name, _pos, _size) {
		transform->position = _pos;
		transform->scale = _scale;

		SetLayer(-1000);
	}

	void Update() override {
		Image::Update();

		float dt = timeManager->GetDeltaTime();

		transform->position.x -= scrollSpeed * dt;

		if(transform->position.x <= -textureSize.x * transform->scale.x) {
			transform->position.x = 0;
		}
	}
};
