#pragma once
#include "EnemyState.h"

class IdleState : public EnemyState {
private:
	float timer = 0.f;
	float duration;

public:
	IdleState(Vector2* pos, float seconds)
		: EnemyState(pos), duration(seconds) {}

	void Update(float dt) override {
		timer += dt;
		if(timer >= duration) finished = true;
	}
};
