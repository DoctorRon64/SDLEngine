#pragma once
#include "../custom/Enemy.h"
#include "states/MoveToTargetState.h"

class BeholderEnemy : public Enemy {
private:
	Vector2 target;

public:
	BeholderEnemy(Vector2 spawn)
		: Enemy(ENEMY_BEHOLDER_SPRITE_PATH, spawn, { 32,32 }) {
		stateManager.SetState(new MoveToTargetState(transform));
		InitHp(3);
	}

	void PickNewTarget() {
		int screenWidth = RenderManager::GetInstance()->WINDOW_WIDTH;
		int screenHeight = RenderManager::GetInstance()->WINDOW_HEIGHT;

		target.x = (float)Randomness::Range(0, screenWidth);
		target.y = (float)Randomness::Range(0, screenHeight);
	}

	void UpdateState(float dt) override {
		MoveTowards(transform, target, speed, dt);
		if((transform->position - target).Length() < 10.f) {
			PickNewTarget();
		}
	}
};
