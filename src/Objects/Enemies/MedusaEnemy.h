#pragma once
#include "../custom/Enemy.h"
#include "states/LinearMoveState.h"

class MedusaEnemy : public Enemy {
public:
	MedusaEnemy(Vector2 spawn)
		: Enemy(ENEMY_MEDUSA_SPRITE_PATH, spawn, { 32, 32 }) {
		float dir = (rand() % 2 == 0) ? -1.f : 1.f;
		float randomSpeed = Randomness::Range(10.f, 50.f);

		Vector2 endPos = spawn + Vector2(dir * 200.f, 0.f); // move left/right
		stateManager.AddState(new LinearMoveState(&transform->position, spawn, endPos, randomSpeed));
		InitHp(2);
	}
};