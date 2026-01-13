#pragma once
#include "../custom/Enemy.h"
#include "states/LinearMoveState.h"

class BubbleEnemy : public Enemy {
private:
	float angle = 0.f;
	Vector2 circleCenter;

public:
	BubbleEnemy(Vector2 spawn)
		: Enemy(ENEMY_BUBBLE_SPRITE_PATH, spawn, { 32, 32 }) {
		stateManager.SetState(new LinearMoveState(transform, { -speed, 0 }));
		InitHp(2);
	}

protected:

	void UpdateState(float dt) override {
		switch(state) {
			case EnemyState::SIMPLE_MOVE: MoveStraight(dt); break;
			case EnemyState::CIRCLE_MOVE: MoveCircle(dt); break;
			case EnemyState::CHASE: MoveStraight(dt); break;
		}
	}

	void MoveStraight(float dt) {
		transform->position += velocity * dt;

		if(transform->position.x < RenderManager::GetInstance()->WINDOW_WIDTH * 0.66f) {
			state = EnemyState::CIRCLE_MOVE;
			circleCenter = transform->position;
			angle = 0.f;
		}
	}

	void MoveCircle(float dt) {
		const float DEG2RAD = 3.14159265f / 180.0f;
		float radius = 100.f;
		angle += 180.f * dt;

		float rad = angle * DEG2RAD;
		transform->position.x = circleCenter.x + cos(rad) * radius;
		transform->position.y = circleCenter.y + sin(rad) * radius;

		if(angle >= 300.f) {
			state = EnemyState::CHASE;
			velocity = { -speed * 1.5f, 0 };
		}
	}
};
