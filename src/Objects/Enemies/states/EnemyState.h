#pragma once
#include "math/Vector2.h"

class Transform;

class EnemyState {
protected:
	Vector2* transformPos; // pointer to enemy position
	bool finished = false;

public:
	EnemyState(Vector2* pos) : transformPos(pos) {}
	virtual ~EnemyState() = default;

	virtual void Update(float dt) = 0;

	bool IsFinished() const { return finished; }
	virtual EnemyState* NextState() { return nullptr; }
};