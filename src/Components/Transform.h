#pragma once

class Transform {
private:
	Vector2 size;
public:
	Vector2 position;
	float rotation;
	Vector2 scale;

	Transform() :
		position(Vector2(0.f, 0.f)), rotation(0.f), scale(Vector2(1.f, 1.f)), size(Vector2(100.f, 100.f)) {}
	Transform(Vector2 _position, float _rotation, Vector2 _scale, Vector2 _size) :
		position(_position), rotation(_rotation), scale(_scale), size(_size) {}

	Vector2 GetSize() { return size * scale; }
	void SetSize(const Vector2& _size) { size = _size; }
};