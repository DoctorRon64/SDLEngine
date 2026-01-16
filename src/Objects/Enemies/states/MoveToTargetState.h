#pragma once
#include "EnemyState.h"
#include "IdleState.h"
#include <math/MoveTowards.h>

class MoveToTargetState : public EnemyState {
	Transform* transform;
	Vector2 target;

public:
	MoveToTargetState(Transform* t)
		: EnemyState(&t->position), transform(t) {
		target.x = Randomness::Range(0, RenderManager::GetInstance()->WINDOW_WIDTH);
		target.y = Randomness::Range(0, RenderManager::GetInstance()->WINDOW_HEIGHT);
	}

	void Update(float dt) override {
		MoveTowards(transform, target, 60.f, dt);
	}

	bool IsFinished() const override {
		return (transform->position - target).Length() < 10.f;
	}

	EnemyState* NextState() override {
		return new IdleState(&transform->position, 0.5f);
	}
};
