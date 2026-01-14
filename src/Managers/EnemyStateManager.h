#pragma once
#include "../objects/enemies/states/EnemyState.h"

class EnemyStateManager {
private:
	std::vector<EnemyState*> states;
	size_t currentIndex = 0;

public:
	EnemyStateManager() = default;
	~EnemyStateManager() {
		for(auto* s : states) delete s;
	}

	void AddState(EnemyState* state) { states.push_back(state); }

	void Update(float dt) {
		if(currentIndex >= states.size()) return;

		EnemyState* state = states[currentIndex];
		state->Update(dt);

		if(state->IsFinished()) {
			if(EnemyState* next = state->NextState()) {
				delete state;
				states[currentIndex] = next;
			}
			else {
				currentIndex++;
			}
		}
	}

	bool IsFinished() const { return currentIndex >= states.size(); }

	EnemyState* GetCurrentState() {
		return currentIndex < states.size() ? states[currentIndex] : nullptr;
	}
};