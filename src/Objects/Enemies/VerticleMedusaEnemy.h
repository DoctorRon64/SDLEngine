#pragma once
#include "../custom/Enemy.h"

class VerticalMedusaEnemy : public Enemy {
	float moveTime = 1.2f;
	float pauseTime = 0.8f;
	bool moving = true;

	void UpdateState(float dt) override {
		if(moving) {
			transform->position.y -= speed * dt;
			if(stateTimer >= moveTime) {
				moving = false;
				stateTimer = 0;
			}
		}
		else {
			if(stateTimer >= pauseTime) {
				moving = true;
				stateTimer = 0;
			}
		}
	}
};
