#pragma once
#include "../custom/Enemy.h"
#include "states/LinearMoveState.h"

class BubbleEnemy : public Enemy {
public:
	BubbleEnemy(Vector2 spawn) : Enemy(ENEMY_BUBBLE_SPRITE_PATH, spawn, { 32, 32 }) {
		Vector2 circleCenter = { spawn.x + 150.f, spawn.y };
		stateManager.AddState(new LinearMoveState(&transform->position, spawn, circleCenter, 50.f));
		stateManager.AddState(new CircleMoveState(&transform->position, circleCenter, 100.f, 180.f, 1));
		stateManager.AddState(new LinearMoveState(&transform->position, circleCenter, { circleCenter.x - 200.f, circleCenter.y }, 80.f));
	}
};
