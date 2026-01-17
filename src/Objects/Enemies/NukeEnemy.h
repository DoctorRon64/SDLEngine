#pragma once
#include "../custom/Enemy.h"
#include "states/VelocityMoveState.h"

class NukeEnemy : public Enemy {
public:
	NukeEnemy(Vector2 spawn)
		: Enemy(ENEMY_NUKE_SPRITE_PATH, spawn, { 32, 32 }) {
		float x = Randomness::Range(0.f, RenderManager::GetInstance()->WINDOW_WIDTH);
		float y = RenderManager::GetInstance()->WINDOW_HEIGHT + transform->GetSize().y;
		transform->position = { x, y };
		stateManager.AddState(new VelocityMoveState(&transform->position, { 0.f, -90.f }));
		InitHp(25);
	}

	const std::string& GetDeathSfx() const override { return SFX_ENEMY_NUKE_DEATH_PATH; }
};
