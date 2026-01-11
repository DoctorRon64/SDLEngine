#pragma once
#include "../custom/Enemy.h"

class MedusaEnemy : public Enemy {
public:
	MedusaEnemy(Vector2 spawn)
		: Enemy(ENEMY_MEDUSA_SPRITE_PATH, spawn, { 32, 32 }) {
		float dir = (rand() % 2 == 0) ? -1.f : 1.f;
		speed = Randomness::Range(10.f, 50.f);
		velocity = { dir * speed, 0 };
		InitHp(2);
	}

protected:
	void UpdateState(float dt) override {
		transform->position += velocity * dt;
	}
};
