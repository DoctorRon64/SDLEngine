#pragma once
#include "EnemyState.h"

class ArcMoveState : public EnemyState {
private:
	Vector2 center;
	float radius;
	float degreesPerSec;
	float angle = 0.f;
	float endAngle = 0.f;

public:
	ArcMoveState(Vector2* pos, Vector2 c, float r, float degPerSec, float arcDegrees, float startAngle = 0.f)
		: EnemyState(pos),
		center(c),
		radius(r),
		degreesPerSec(degPerSec),
		angle(startAngle) {
		endAngle = startAngle + arcDegrees;
	}

	void Update(float dt) override {
		angle += degreesPerSec * dt;
		float rad = angle * 3.14159265f / 180.0f;
		transformPos->x = center.x + cos(rad) * radius;
		transformPos->y = center.y + sin(rad) * radius;

		if(angle >= endAngle) finished = true;
	}
};
