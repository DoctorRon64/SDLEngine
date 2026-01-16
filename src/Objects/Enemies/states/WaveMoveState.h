#pragma once
#include "EnemyState.h"
#include "WaveMoveState.h"

class WaveMoveState : public EnemyState {
private:
	float time = 0.f;

public:
	WaveMoveState(Vector2* pos) : EnemyState(pos) {}

	void Update(float dt) override {
		time += dt;
		transformPos->x -= 100.f * dt;           // horizontal speed
		transformPos->y += sin(time * 5.f) * 50.f * dt; // vertical sine wave
	}
};