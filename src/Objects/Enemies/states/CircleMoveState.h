#pragma once
#include "EnemyState.h"

class CircleMoveState : public EnemyState {
	Transform* transform;
	Vector2 center;
	float radius;
	float angle = 0.f;
	float degreesPerSec;

public:
	CircleMoveState(Transform* t, Vector2 c, float r, float dps)
		: transform(t), center(c), radius(r), degreesPerSec(dps) {}

	void Update(float dt) override {
		angle += degreesPerSec * dt;
		float rad = angle * 3.14159f / 180.f;

		transform->position.x = center.x + cos(rad) * radius;
		transform->position.y = center.y + sin(rad) * radius;
	}
};
