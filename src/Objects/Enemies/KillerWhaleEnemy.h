#pragma once
#include "../custom/Enemy.h"

class KillerWhaleEnemy : public Enemy {
	float waveTime = 0.f;

public:
	KillerWhaleEnemy(Vector2 spawn)
		: Enemy("res/enemies/whale.png", spawn, { 256,128 }) {
		velocity = { -speed, 0 };
	}

protected:
	void UpdateState(float dt) override {
		waveTime += dt;

		transform->position.x += velocity.x * dt;
		transform->position.y += sin(waveTime * 5.f) * 50.f * dt;
	}
};
