#pragma once
#include "../custom/Enemy.h"
#include "states/IdleState.h"
#include "states/LinearMoveState.h"

class UfoEnemy : public Enemy {
public:
	UfoEnemy(Vector2 spawn)
		: Enemy(ENEMY_UFO_SPRITE_PATH, spawn, { 32, 32 }) {
		bool fromLeft = false;
		float startX = fromLeft ? -transform->GetSize().x : RenderManager::GetInstance()->WINDOW_WIDTH + transform->GetSize().x;
		float startY = Randomness::Range(0.f, RenderManager::GetInstance()->WINDOW_HEIGHT);
		transform->position = { startX, startY };

		Vector2 mid = { RenderManager::GetInstance()->WINDOW_WIDTH / 2.f, startY };
		Vector2 exit = { startX, startY };

		stateManager.AddState(new LinearMoveState(&transform->position, transform->position, mid, 220.f));
		stateManager.AddState(new IdleState(&transform->position, 0.75f));
		stateManager.AddState(new LinearMoveState(&transform->position, mid, exit, 220.f));

		InitHp(30);
	}
};
