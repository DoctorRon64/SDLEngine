#pragma once
#include "EnemyState.h"

class VerticalStepState : public EnemyState {
private:
	float stepDistance;
	float speed;
	float pauseDuration;
	float moved = 0.f;
	float pauseTimer = 0.f;
	bool pausing = false;

public:
	VerticalStepState(Vector2* pos, float step, float pixelsPerSec, float pauseSeconds)
		: EnemyState(pos),
		stepDistance(step),
		speed(pixelsPerSec),
		pauseDuration(pauseSeconds) {}

	void Update(float dt) override {
		if(pausing) {
			pauseTimer += dt;
			if(pauseTimer >= pauseDuration) {
				pausing = false;
				pauseTimer = 0.f;
				moved = 0.f;
			}
			return;
		}

		float delta = speed * dt;
		transformPos->y -= delta;
		moved += delta;

		if(moved >= stepDistance) {
			pausing = true;
		}
	}
};
