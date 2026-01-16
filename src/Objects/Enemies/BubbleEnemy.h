#pragma once
#include "../custom/Enemy.h"
#include "states/ArcMoveState.h"
#include "states/LinearMoveState.h"

class BubbleEnemy : public Enemy {
public:
	BubbleEnemy(Vector2 spawn) : Enemy(ENEMY_BUBBLE_SPRITE_PATH, spawn, { 32, 32 }) {
		float enterX = RenderManager::GetInstance()->WINDOW_WIDTH / 3.f;
		Vector2 enterPos = { enterX, spawn.y };

		float radius = 90.f;
		Vector2 arcCenter = enterPos + Vector2(-radius, 0.f);
		float arcDegrees = 300.f;

		Vector2* pos = &transform->position;
		stateManager.AddState(new LinearMoveState(pos, spawn, enterPos, 60.f));
		stateManager.AddState(new ArcMoveState(pos, arcCenter, radius, 180.f, arcDegrees, 0.f));

		float arcEndRad = arcDegrees * 3.14159265f / 180.0f;
		Vector2 arcEnd = {
			arcCenter.x + cos(arcEndRad) * radius,
			arcCenter.y + sin(arcEndRad) * radius
		};
		Vector2 lineEnd = arcEnd + Vector2(-400.f, 0.f);
		stateManager.AddState(new LinearMoveState(pos, arcEnd, lineEnd, 90.f));
		InitHp(20);
	}
};
