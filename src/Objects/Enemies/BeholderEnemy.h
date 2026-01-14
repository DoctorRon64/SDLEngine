#pragma once
#include "../custom/Enemy.h"
#include "states/MoveToTargetState.h"

class BeholderEnemy : public Enemy {
public:
	BeholderEnemy(Vector2 spawn) : Enemy(ENEMY_BEHOLDER_SPRITE_PATH, spawn, { 32, 32 }) {
		stateManager.AddState(new MoveToTargetState(transform));
		InitHp(3);
	}

	virtual void Update() override {
		Enemy::Update();
	}
};