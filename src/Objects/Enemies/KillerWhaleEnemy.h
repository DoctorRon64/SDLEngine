#pragma once
#include "../custom/Enemy.h"
#include "states/LinearMoveState.h"
#include "states/WaveMoveState.h"

class KillerWhaleEnemy : public Enemy {
public:
	KillerWhaleEnemy(Vector2 spawn)
		: Enemy(ENEMY_WHALE_SPRITE_PATH, spawn, { 32, 32 }) {
		float h = (float)RenderManager::GetInstance()->WINDOW_HEIGHT;
		float heightOffset = transform->GetSize().y;
		bool fromTop = Randomness::Range(0, 1) == 0;

		Vector2 start = { spawn.x, fromTop ? 0.f : (h - heightOffset) };
		Vector2 detachTarget = start + Vector2(0.f, fromTop ? 80.f : -80.f);
		transform->position = start;

		stateManager.AddState(new LinearMoveState(&transform->position, start, detachTarget, 80.f));
		stateManager.AddState(new WaveMoveState(&transform->position));
		InitHp(40);
	}

	const std::string& GetDeathSfx() const override { return SFX_ENEMY_WHALE_DEATH_PATH; }
};
