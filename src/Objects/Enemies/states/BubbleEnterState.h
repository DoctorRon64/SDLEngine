#pragma once
#include "CircleMoveState.h"
#include "EnemyState.h"

class BubbleEnterState : public EnemyState {
	float speed = 50.f;
	float enterX;

public:
	BubbleEnterState(Vector2* pos)
		: EnemyState(pos) {
		enterX = RenderManager::GetInstance()->WINDOW_WIDTH * 0.66f;
	}

	void Update(float dt) override {
		transformPos->x -= speed * dt;

		if(transformPos->x < enterX) {
			finished = true;
		}
	}

	EnemyState* NextState() override {
		return new CircleMoveState(transformPos, *transformPos, 100.f, 180.f, 1);
	}
};
