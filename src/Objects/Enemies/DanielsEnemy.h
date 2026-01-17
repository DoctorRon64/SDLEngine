#pragma once
#include "../custom/Enemy.h"
#include "states/LinearMoveState.h"

class DanielsEnemy : public Enemy {
public:
	DanielsEnemy(Vector2 spawn)
		: Enemy(ENEMY_DANIELS_SPRITE_PATH, spawn, { 32, 32 }) {
		bool fromTop = (Randomness::Range(0, 1) == 0);
		float startY = fromTop ? 0.f : (RenderManager::GetInstance()->WINDOW_HEIGHT - transform->GetSize().y);
		float startX = RenderManager::GetInstance()->WINDOW_WIDTH + transform->GetSize().x;
		transform->position = { startX, startY };

		float midX = RenderManager::GetInstance()->WINDOW_WIDTH * 0.25f;
		float midY = RenderManager::GetInstance()->WINDOW_HEIGHT / 2.f;

		stateManager.AddState(new LinearMoveState(&transform->position, transform->position, { midX, startY }, 120.f));
		stateManager.AddState(new LinearMoveState(&transform->position, { midX, startY }, { midX, midY }, 120.f));
		stateManager.AddState(new LinearMoveState(&transform->position, { midX, midY }, { -transform->GetSize().x, midY }, 120.f));

		InitHp(30);
	}

	const std::string& GetDeathSfx() const override { return SFX_ENEMY_DANIELS_DEATH_PATH; }
};
