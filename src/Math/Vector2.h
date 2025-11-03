#pragma once
#include <cassert>
#include <cmath>

struct Vector2 {
public:
	float x;
	float y;

	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}

	Vector2 operator+(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}

	bool operator==(const Vector2& other) const {
		return (x == other.x && y == other.y);
	}

	Vector2 operator-(const Vector2& other) const {
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator*(const float scalar) const {
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator*(const Vector2& other) const {
		return Vector2(x * other.x, y * other.y);
	}

	Vector2 operator/(const float scalar) const {
		assert(scalar != 0.0f && "Division by zero in Vector2");
		return Vector2(x / scalar, y / scalar);
	}

	Vector2& operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2& operator*=(const float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2& operator/=(const float scalar) {
		assert(scalar != 0.0f && "Division by zero in Vector2");
		x /= scalar;
		y /= scalar;
		return *this;
	}

	Vector2 operator-() const {
		return Vector2(-x, -y);
	}

	void Normalize() {
		float length = sqrtf(x * x + y * y);
		if(length != 0.0f) {
			x /= length;
			y /= length;
		}
	}

	Vector2 GetNormalized() const {
		Vector2 result = *this;
		result.Normalize();
		return result;
	}

	float Dot(const Vector2& other) const {
		return x * other.x + y * other.y;
	}

	float Length() const {
		return sqrtf(x * x + y * y);
	}

	float LengthSquared() const {
		return x * x + y * y;
	}
};
