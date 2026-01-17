#pragma once
#include "../custom/Enemy.h"
#include "states/LinearMoveState.h"

class AngrygonEnemy : public Enemy {
public:
	AngrygonEnemy(Vector2 spawn)
		: Enemy(ENEMY_ANGRYGON_SPRITE_PATH, spawn, { 32, 32 }) {
		float startX = RenderManager::GetInstance()->WINDOW_WIDTH + transform->GetSize().x;
		float startY = Randomness::Range(100.f, RenderManager::GetInstance()->WINDOW_HEIGHT - 100.f);
		transform->position = { startX, startY };

		float stepX = 200.f;
		float stepY = 160.f;
		float speed = 140.f;

		Vector2 p1 = { startX - stepX, startY };
		Vector2 p2 = { p1.x, std::min(RenderManager::GetInstance()->WINDOW_HEIGHT - transform->GetSize().y, p1.y + stepY) };
		Vector2 p3 = { p2.x - stepX, p2.y };
		Vector2 p4 = { p3.x, std::max(0.f, p3.y - stepY) };

		stateManager.AddState(new LinearMoveState(&transform->position, transform->position, p1, speed));
		stateManager.AddState(new LinearMoveState(&transform->position, p1, p2, speed));
		stateManager.AddState(new LinearMoveState(&transform->position, p2, p3, speed));
		stateManager.AddState(new LinearMoveState(&transform->position, p3, p4, speed));

		InitHp(20);
	}
};
