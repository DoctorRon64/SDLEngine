#pragma once
#include "pch.h"

inline void MoveTowards(Transform* transform, const Vector2& target, float speed, float dt) {
	Vector2 direction = target - transform->position;
	float distance = direction.Length();

	if(distance < 1.f)
		return;

	direction.Normalize();
	transform->position += direction * speed * dt;
}
