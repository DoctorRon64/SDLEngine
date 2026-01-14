#pragma once
#include "../custom/Enemy.h"
#include "states/IdleState.h"
#include "states/LinearMoveState.h"

class VerticalMedusaEnemy : public Enemy {
public:
	VerticalMedusaEnemy(Vector2 spawn)
		: Enemy(ENEMY_VERTICAL_MEDUSA_SPRITE_PATH, spawn, { 32, 32 }) {
		Vector2 upPos = spawn + Vector2(0.f, -100.f); // move up 100 px
		stateManager.AddState(new LinearMoveState(&transform->position, spawn, upPos, 50.f));
		stateManager.AddState(new IdleState(&transform->position, 0.8f));
		stateManager.AddState(new LinearMoveState(&transform->position, upPos, spawn, 50.f));
		stateManager.AddState(new IdleState(&transform->position, 0.8f));
		InitHp(2);
	}

	virtual void Update() override {
		Enemy::Update();
	}
};
