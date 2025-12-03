#pragma once
#include "../ImageObject.h"

class background : public ImageObject {
private:
	float scrollSpeed = 200.0f;

public:
	background(std::string _name = "res/missing.png",
		Vector2 _pos = Vector2(0.f, 0.f),
		Vector2 _size = Vector2(1024.f, 1303.f),
		Vector2 _scale = Vector2(1024.f, 1303.f))
		: ImageObject(_name, _pos, _size) {
		transform->position = _pos;
		transform->scale = _scale;

		SetLayer(-1000);
	}

	void Update() override {
		ImageObject::Update();

		float dt = timeManager->GetDeltaTime();

		transform->position.x -= scrollSpeed * dt;

		if(transform->position.x <= -textureSize.x * transform->scale.x) {
			transform->position.x = 0;
		}
	}
};
