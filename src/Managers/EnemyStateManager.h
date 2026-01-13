#pragma once
#include "../objects/enemies/states/EnemyState.h"

class EnemyStateManager {
private:
	EnemyState* current = nullptr;

public:
	~EnemyStateManager() { delete current; }

	void SetState(EnemyState* state) {
		delete current;
		current = state;
	}

	void Update(float dt) {
		if(!current) return;

		current->Update(dt);

		if(current->IsFinished()) {
			EnemyState* next = current->NextState();
			SetState(next);
		}
	}
};
