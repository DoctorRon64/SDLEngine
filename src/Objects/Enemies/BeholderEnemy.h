#pragma once
#include "../custom/Enemy.h"
#include "states/MoveToTargetState.h"

class BeholderEnemy : public Enemy {
public:
	BeholderEnemy(Vector2 spawn)
		: Enemy(ENEMY_BEHOLDER_SPRITE_PATH, spawn) {
		stateManager.AddState(new MoveToTargetState(&transform->position));
		InitHp(3);
	}
};