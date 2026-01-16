#pragma once
#include "EnemyState.h"

class VelocityMoveState : public EnemyState {
private:
	Vector2 velocity;

public:
	VelocityMoveState(Vector2* pos, Vector2 vel)
		: EnemyState(pos), velocity(vel) {}

	void Update(float dt) override {
		*transformPos += velocity * dt;
	}
};
