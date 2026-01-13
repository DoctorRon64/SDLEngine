#pragma once
#include "CircleMoveState.h"
#include "EnemyState.h"

class BubbleEnterState : public EnemyState {
	Transform* transform;
	EnemyStateManager* manager;

public:
	BubbleEnterState(Transform* t, EnemyStateManager* m)
		: transform(t), manager(m) {}

	void Update(float dt) override {
		transform->position.x -= 50.f * dt;

		if(transform->position.x < RenderManager::GetInstance()->WINDOW_WIDTH * 0.66f) {
			manager->SetState(new CircleMoveState(transform, transform->position, 100.f, 180.f));
		}
	}
};
