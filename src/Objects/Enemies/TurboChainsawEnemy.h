#pragma once
#include "../custom/Enemy.h"
#include "states/CircleMoveState.h"
#include "states/LinearMoveState.h"

class TurboChainsawEnemy : public Enemy {
public:
	TurboChainsawEnemy(Vector2 spawn)
		: Enemy(ENEMY_TURBO_CHAINSAW_SPRITE_PATH, spawn, { 32, 32 }) {
		const float radius = 120.f;
		const float speed = 140.f;
		bool fromLeft = false;

		float startX = fromLeft ? -transform->GetSize().x : RenderManager::GetInstance()->WINDOW_WIDTH + transform->GetSize().x;
		float startY = spawn.y;
		transform->position = { startX, startY };

		float centerX = RenderManager::GetInstance()->WINDOW_WIDTH / 2.f + (fromLeft ? -radius : radius);
		Vector2 center = { centerX, startY };
		Vector2 entry = { center.x + (fromLeft ? radius : -radius), center.y };
		Vector2 exit = { startX, startY };

		stateManager.AddState(new LinearMoveState(&transform->position, transform->position, entry, speed));
		stateManager.AddState(new CircleMoveState(&transform->position, center, radius, 180.f, 1));
		stateManager.AddState(new LinearMoveState(&transform->position, entry, exit, speed));

		InitHp(30);
	}
};
