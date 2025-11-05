#pragma once
#include <Math/Vector2.h>

class AABB {
protected:
	Vector2 topLeft = Vector2(0.0f, 0.0f);
	Vector2 size = Vector2(0.0f, 0.0f);
public:
	AABB(Vector2 _topLeft, Vector2 _size) : topLeft(_topLeft), size(_size) {}

	Vector2 GetTopLeft() const { return topLeft; }
	Vector2 GetSize() const { return size; }
	void SetTopLeft(Vector2 _newTopLeft) { topLeft = _newTopLeft; }
	void SetSize(Vector2 _newSize) { size = _newSize; }

	bool CheckOverlappingPoint(const Vector2 _point);
	bool CheckOverlappingAABB(const AABB* _other);
};