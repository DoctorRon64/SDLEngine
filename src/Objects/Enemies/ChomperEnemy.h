#pragma once
#include "../custom/Enemy.h"

class ChomperEnemy : public Enemy {
private:
	float angle = 0.f;
	Vector2 center;

public:
	ChomperEnemy(Vector2 spawn)
		: Enemy(ENEMY_CHOMPER_SPRITE_PATH, spawn, { 32,32 }) {
		velocity = { -speed, 0 };
		InitHp(4);
	}

	void UpdateState(float dt) override {
		center.x -= speed * 0.3f * dt;
		Orbit(transform, center, 50.f, angle, 2.f, dt);
	}
};
