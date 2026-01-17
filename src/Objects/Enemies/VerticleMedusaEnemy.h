#pragma once
#include "../custom/Enemy.h"
#include "states/VerticalStepState.h"

class VerticalMedusaEnemy : public Enemy {
public:
	VerticalMedusaEnemy(Vector2 spawn)
		: Enemy(ENEMY_VERTICAL_MEDUSA_SPRITE_PATH, spawn, { 32, 32 }) {
		stateManager.AddState(new VerticalStepState(&transform->position, 60.f, 40.f, 0.6f));
		InitHp(30);
	}

	const std::string& GetDeathSfx() const override { return SFX_ENEMY_VERTICAL_MEDUSA_DEATH_PATH; }
};
