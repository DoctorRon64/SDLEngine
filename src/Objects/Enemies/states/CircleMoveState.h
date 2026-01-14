#pragma once
#include "EnemyState.h"

class CircleMoveState : public EnemyState {
private:
	Vector2 center;
	float radius;
	float degreesPerSec;
	float angle = 0.f;
	int rotations;

public:
	CircleMoveState(Vector2* pos, Vector2 c, float r, float degPerSec, int rot = 1)
		: EnemyState(pos), center(c), radius(r), degreesPerSec(degPerSec), rotations(rot) {}

	void Update(float dt) override {
		angle += degreesPerSec * dt;
		float rad = angle * 3.14159265f / 180.0f;
		transformPos->x = center.x + cos(rad) * radius;
		transformPos->y = center.y + sin(rad) * radius;

		if(angle >= 360.f * rotations) finished = true;
	}
};
