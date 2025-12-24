#pragma once
#include "../custom/Enemy.h"

class MedusaEnemy : public Enemy {
public:
	MedusaEnemy(Vector2 spawn)
		: Enemy("res/enemies/medusa_sprite.png", spawn, { 32, 32 }) {
		float dir = (rand() % 2 == 0) ? -1.f : 1.f;
		speed = RandomRange(10.f, 50.f);
		velocity = { dir * speed, 0 };
	}

	float RandomRange(float min, float max) {
		float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		return min + r * (max - min);
	}

protected:
	void UpdateState(float dt) override {
		transform->position += velocity * dt;
	}
};
