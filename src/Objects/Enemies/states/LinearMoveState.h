#pragma once
#include "EnemyState.h"

class LinearMoveState : public EnemyState {
	Transform* transform;
	Vector2 velocity;

public:
	LinearMoveState(Transform* t, Vector2 v)
		: transform(t), velocity(v) {}

	void Update(float dt) override {
		transform->position += velocity * dt;
	}
};