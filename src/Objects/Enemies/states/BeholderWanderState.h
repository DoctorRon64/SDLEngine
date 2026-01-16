#pragma once
#include "EnemyState.h"
#include "math/Random.h"

class BeholderWanderState : public EnemyState {
private:
	float speed;
	float moveDuration;
	float pauseDuration;
	float timer = 0.f;
	bool moving = true;
	Vector2 direction = { 1.f, 0.f };

	void PickDirection() {
		float angle = Randomness::Range(0.f, 6.2831853f);
		direction = { cos(angle), sin(angle) };

		float margin = 80.f;
		float w = (float)RenderManager::GetInstance()->WINDOW_WIDTH;
		float h = (float)RenderManager::GetInstance()->WINDOW_HEIGHT;

		if(transformPos->x < margin) direction.x = fabs(direction.x);
		if(transformPos->x > w - margin) direction.x = -fabs(direction.x);
		if(transformPos->y < margin) direction.y = fabs(direction.y);
		if(transformPos->y > h - margin) direction.y = -fabs(direction.y);

		if(direction.Length() == 0.f) direction = { 1.f, 0.f };
		direction.Normalize();
	}

public:
	BeholderWanderState(Vector2* pos, float pixelsPerSec, float moveSeconds, float pauseSeconds)
		: EnemyState(pos),
		speed(pixelsPerSec),
		moveDuration(moveSeconds),
		pauseDuration(pauseSeconds) {
		PickDirection();
	}

	void Update(float dt) override {
		timer += dt;

		if(moving) {
			*transformPos += direction * speed * dt;
			if(timer >= moveDuration) {
				moving = false;
				timer = 0.f;
			}
			return;
		}

		if(timer >= pauseDuration) {
			moving = true;
			timer = 0.f;
			PickDirection();
		}
	}
};
