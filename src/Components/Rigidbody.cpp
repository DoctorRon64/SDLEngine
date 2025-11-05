#include "pch.h"
#include "Rigidbody.h"
#include <Math/AABB.h>

bool RigidBody::CheckCollision(const RigidBody* _other) {
	for(AABB* ownCollider : colliders) {
		for(AABB* otherCollider : _other->colliders) {
			if(ownCollider->CheckOverlappingAABB(otherCollider)) {
				return true;
			}
		}
	}
	return false;
}

bool RigidBody::CheckOverlappingPoint(Vector2 _point) {
	for(AABB* ownCollider : colliders) {
		if(ownCollider->CheckOverlappingPoint(_point)) {
			return true;
		}
	}
	return false;
}

void RigidBody::Update(float _deltaTime) {
	velocity += acceleration * _deltaTime;
	angularVelocity += angularAcceleration * _deltaTime;

	velocity *= 1.0f / (1.0f + _deltaTime * linearDrag);
	angularVelocity *= 1.0f / (1.0f + _deltaTime * angularDrag);

	transform->position += velocity * _deltaTime;
	transform->rotation += angularVelocity * _deltaTime;

	acceleration = Vector2();
	angularAcceleration = 0.0f;

	Vector2 offset = (Vector2(-transform->size.x, -transform->size.y) / 2.0f) * transform->scale;
	for(AABB* collider : colliders) {
		collider->SetTopLeft(transform->position + offset);
		collider->SetSize(transform->size * transform->scale);
	}
}