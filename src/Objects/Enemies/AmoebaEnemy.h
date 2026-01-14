#pragma once
#include "../custom/Enemy.h"
#include "states/CircleMoveState.h"
#include "states/LinearMoveState.h"

class AmoebaEnemy : public Enemy {
public:
	AmoebaEnemy(Vector2 spawn)
		: Enemy(ENEMY_AMOEBA_SPRITE_PATH, spawn, { 32, 32 }) {
		Vector2 center(RenderManager::GetInstance()->WINDOW_WIDTH / 2.f,
					   RenderManager::GetInstance()->WINDOW_HEIGHT / 2.f);

		stateManager.AddState(new LinearMoveState(&transform->position, spawn, center, 100.f));
		stateManager.AddState(new CircleMoveState(&transform->position, center, 80.f, 180.f, 2));
		stateManager.AddState(new LinearMoveState(&transform->position, center, { spawn.x - 50.f, center.y }, 100.f));
	}
};
