#pragma once
#include "../custom/Enemy.h"
#include "states/CircleMoveState.h"
#include "states/LinearMoveState.h"

class ChomperEnemy : public Enemy {
public:
	ChomperEnemy(Vector2 spawn) : Enemy(ENEMY_CHOMPER_SPRITE_PATH, spawn, { 32, 32 }) {
		Vector2 leftTarget = spawn + Vector2(-200.f, 0.f);

		stateManager.AddState(new LinearMoveState(&transform->position, spawn, leftTarget, 50.f));
		stateManager.AddState(new CircleMoveState(&transform->position, leftTarget, 50.f, 90.f, 2));
		InitHp(4);
	}
};
