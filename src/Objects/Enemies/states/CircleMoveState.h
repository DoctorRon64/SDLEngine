#pragma once
#include "EnemyState.h"

class CircleMoveState : public EnemyState {
private:
	Vector2 center;
	float radius;
	float degreesPerSec;
	float angle = 0.f;
	float endAngle = 0.f;
	int rotations;

public:
	CircleMoveState(Vector2* pos, Vector2 c, float r, float degPerSec, int rot = 1, float startAngle = 0.f)
		: EnemyState(pos),
		center(c),
		radius(r),
		degreesPerSec(degPerSec),
		angle(startAngle),
		rotations(rot) {
		endAngle = startAngle + (360.f * rotations);
	}

	void Update(float dt) override {
		angle += degreesPerSec * dt;
		float rad = angle * 3.14159265f / 180.0f;
		transformPos->x = center.x + cos(rad) * radius;
		transformPos->y = center.y + sin(rad) * radius;

		if(angle >= endAngle) finished = true;
	}
};
