#include "pch.h"
#include "AABB.h"

bool AABB::CheckOverlappingPoint(const Vector2 _point) {
	const bool isInsideX = _point.x >= topLeft.x && _point.x <= topLeft.x + size.x;
	const bool isInsideY = _point.y >= topLeft.y && _point.y <= topLeft.y + size.y;

	return isInsideX && isInsideY;
}

bool AABB::CheckOverlappingAABB(const AABB* _other) {
	bool intersectionX = false;
	intersectionX |= topLeft.x >= _other->topLeft.x &&
		topLeft.x <= _other->topLeft.x + _other->size.x;
	intersectionX |= _other->topLeft.x >= topLeft.x &&
		_other->topLeft.x <= topLeft.x + size.x;

	bool intersectionY = false;
	intersectionY |= topLeft.y >= _other->topLeft.y &&
		topLeft.y <= _other->topLeft.y + _other->size.y;
	intersectionY |= _other->topLeft.y >= topLeft.y
		&& _other->topLeft.y <= topLeft.y + size.y;

	return intersectionX && intersectionY;
}