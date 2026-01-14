#pragma once
#include "EnemyState.h"

class LinearMoveState : public EnemyState {
private:
	Vector2 start;
	Vector2 end;
	float speed;

public:
	LinearMoveState(Vector2* pos, Vector2 s, Vector2 e, float pixelsPerSec)
		: EnemyState(pos), start(s), end(e), speed(pixelsPerSec) {
		*transformPos = start;
	}

	void Update(float dt) override {
		Vector2 dir = end - *transformPos;
		float distance = dir.Length();
		if(distance < 1.f) {
			*transformPos = end;
			finished = true;
			return;
		}
		dir.Normalize();
		*transformPos += dir * speed * dt;
	}
};
