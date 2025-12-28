#pragma once
#include "../AnimatedImage.h"
class Explosion :
    public AnimatedImage
{
public:
	Explosion() : AnimatedImage("res/explosion.png", { 0.f, 0.f }, { 100.f, 100.f }, 49, 13, 100.f, 100.f, 5, true) {
		transform->scale = Vector2(3.f, 3.f);
	}

	virtual void Update() override {
		Object::Update();
	}
};

