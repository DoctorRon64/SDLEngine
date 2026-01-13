#pragma once
#include "EnemyState.h"

class IdleState : public EnemyState {
	float timer = 0.f;
	float duration;

public:
	IdleState(float d) : duration(d) {}

	void Update(float dt) override {
		timer += dt;
	}

	bool IsFinished() const override {
		return timer >= duration;
	}
};
