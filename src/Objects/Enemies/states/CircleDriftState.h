#pragma once
#include "EnemyState.h"

class CircleDriftState : public EnemyState {
private:
	Vector2 center;
	float radius;
	float degreesPerSec;
	float driftSpeed;
	float angle = 0.f;

public:
	CircleDriftState(Vector2* pos, Vector2 startCenter, float r, float degPerSec, float drift)
		: EnemyState(pos),
		center(startCenter),
		radius(r),
		degreesPerSec(degPerSec),
		driftSpeed(drift) {}

	void Update(float dt) override {
		center.x -= driftSpeed * dt;
		angle += degreesPerSec * dt;

		float rad = angle * 3.14159265f / 180.0f;
		transformPos->x = center.x + cos(rad) * radius;
		transformPos->y = center.y + sin(rad) * radius;
	}
};
