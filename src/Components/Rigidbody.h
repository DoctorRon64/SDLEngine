#pragma once
#include "Components/Transform.h"
#include "Math/AABB.h"

class RigidBody {
private:
	std::vector <AABB*> colliders;
	Transform* transform;

	Vector2 velocity;
	float angularVelocity;
	Vector2 acceleration;
	float angularAcceleration;
	float linearDrag;
	float angularDrag;
public:
	RigidBody(Transform* _transform)
		: transform(_transform), velocity(Vector2()), angularVelocity(0.0f),
		acceleration(Vector2()), angularAcceleration(0.0f),
		linearDrag(0.0f), angularDrag(0.0f) {}

	~RigidBody() {
		for(AABB* collider : colliders) {
			delete collider;
		}
	}

	void AddCollider(AABB* _collider) { colliders.push_back(_collider); }
	void AddForce(Vector2 _force) { acceleration = acceleration + _force; }
	void AddTorque(float _amount) { angularAcceleration += _amount; }

	Vector2 GetVelocity() const { return velocity; }
	void SetVelocity(const Vector2 _velocity) { velocity = _velocity; }
	void SetLinearDrag(float _linearDrag) { linearDrag = _linearDrag; }
	void SetAngularDrag(float _angularDrag) { angularDrag = _angularDrag; }

	bool CheckCollision(const RigidBody* _other);
	bool CheckOverlappingPoint(Vector2 _point);
	void Update(float _deltaTime);
};