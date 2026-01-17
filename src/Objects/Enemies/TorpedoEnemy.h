#pragma once
#include "../custom/Enemy.h"
#include "states/VelocityMoveState.h"

class TorpedoEnemy : public Enemy {
public:
	TorpedoEnemy(Vector2 spawn)
		: Enemy(ENEMY_TORPEDO_SPRITE_PATH, spawn, { 32, 32 }) {
		float randomSpeed = Randomness::Range(10.f, 50.f);
		stateManager.AddState(new VelocityMoveState(&transform->position, { -randomSpeed, 0.f }));
		InitHp(30);
	}

	const std::string& GetDeathSfx() const override { return SFX_ENEMY_TORPEDO_DEATH_PATH; }
};
