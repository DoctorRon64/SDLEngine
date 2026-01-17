#pragma once
#include "../custom/Enemy.h"
#include "states/VelocityMoveState.h"

class MissileEnemy : public Enemy {
public:
	MissileEnemy(Vector2 spawn)
		: Enemy(ENEMY_MISSILE_SPRITE_PATH, spawn, { 32, 32 }) {
		float x = RenderManager::GetInstance()->WINDOW_WIDTH + transform->GetSize().x;
		float y = Randomness::Range(0.f, RenderManager::GetInstance()->WINDOW_HEIGHT);
		transform->position = { x, y };
		stateManager.AddState(new VelocityMoveState(&transform->position, { -140.f, 0.f }));
		InitHp(25);
	}

	const std::string& GetDeathSfx() const override { return SFX_ENEMY_MISSILE_DEATH_PATH; }
};
