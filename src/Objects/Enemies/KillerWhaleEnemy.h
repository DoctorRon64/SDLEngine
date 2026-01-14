#pragma once
#include "../custom/Enemy.h"
#include "states/WaveMoveState.h"

class KillerWhaleEnemy : public Enemy {
public:
	KillerWhaleEnemy(Vector2 spawn)
		: Enemy(ENEMY_WHALE_SPRITE_PATH, spawn, { 32, 32 }) {
		stateManager.AddState(new WaveMoveState(&transform->position));
		InitHp(3);
	}

	virtual void Update() override {
		Enemy::Update();
	}
};