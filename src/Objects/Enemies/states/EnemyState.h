#pragma once
#include "math/Vector2.h"

class Transform;

class EnemyState {
public:
	virtual ~EnemyState() = default;
	virtual void Update(float dt) = 0;
	virtual bool IsFinished() const { return false; }
	virtual EnemyState* NextState() { return nullptr; }
};
