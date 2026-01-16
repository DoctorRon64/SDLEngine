#pragma once
#include "../custom/Enemy.h"
#include "states/VelocityMoveState.h"

class MedusaEnemy : public Enemy {
public:
	MedusaEnemy(Vector2 spawn)
		: Enemy(ENEMY_MEDUSA_SPRITE_PATH, spawn, { 32, 32 }) {
		float dir = (Randomness::Range(0, 1) == 0) ? -1.f : 1.f;
		float randomSpeed = Randomness::Range(10.f, 50.f);

		stateManager.AddState(new VelocityMoveState(&transform->position, { dir * randomSpeed, 0.f }));
		InitHp(20);
	}
};
