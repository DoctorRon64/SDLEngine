#pragma once
#include "EnemyState.h"

class WaveMoveState : public EnemyState {
	Transform* transform;
	float time = 0.f;

public:
	WaveMoveState(Transform* t) : transform(t) {}

	void Update(float dt) override {
		time += dt;
		transform->position.x -= 60.f * dt;
		transform->position.y += sin(time * 5.f) * 50.f * dt;
	}
};
