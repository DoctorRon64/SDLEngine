#pragma once
#include "../custom/Enemy.h"

class ChomperEnemy : public Enemy {
	float angle = 0.f;
	Vector2 center;

	void UpdateState(float dt) override {
		center.x -= speed * 0.3f * dt;
		Orbit(transform, center, 50.f, angle, 2.f, dt);
	}
};
