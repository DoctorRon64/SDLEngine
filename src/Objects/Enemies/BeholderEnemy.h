#pragma once
#include "../custom/Enemy.h"
#include "states/BeholderWanderState.h"

class BeholderEnemy : public Enemy {
public:
	BeholderEnemy(Vector2 spawn) : Enemy(ENEMY_BEHOLDER_SPRITE_PATH, spawn, { 32, 32 }) {
		stateManager.AddState(new BeholderWanderState(&transform->position, 60.f, 0.8f, 0.4f));
		InitHp(35);
	}
};
