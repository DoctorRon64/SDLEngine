#pragma once
#include "EnemyState.h"

class AmoebaEnemy;

class AmoebaSplitState : public EnemyState {
private:
	AmoebaEnemy* owner = nullptr;
	bool spawned = false;

public:
	AmoebaSplitState(Vector2* pos, AmoebaEnemy* enemy)
		: EnemyState(pos), owner(enemy) {}

	void Update(float dt) override;
};
