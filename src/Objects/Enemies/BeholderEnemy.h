#pragma once
#include "../custom/Enemy.h"

class Beholder : public Enemy {
	Vector2 target;

	void PickNewTarget() {
		target = {
			Random::Range(0, RenderManager::GetInstance()->WINDOW_WIDTH),
			Random::Range(0, RenderManager::GetInstance()->WINDOW_HEIGHT)
		};
	}

	void UpdateState(float dt) override {
		MoveTowards(transform, target, speed, dt);
		if((transform->position - target).Length() < 10.f) {
			PickNewTarget();
		}
	}
};
