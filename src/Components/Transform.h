#pragma once
#include "Math/Vector2.h"

class Transform {
public:
	Vector2 position;
	float rotation;
	Vector2 scales;
	Vector2 size;

	Transform() :
		position(Vector2(0.f, 0.f)), rotation(0.f), scales(Vector2(1.f, 1.f)), size(Vector2(100.f, 100.f)) {
	}
	Transform(Vector2 _position, float _rotation, Vector2 _scale, Vector2 _size) :
		position(_position), rotation(_rotation), scales(_scale), size(_size) {
	}
};
