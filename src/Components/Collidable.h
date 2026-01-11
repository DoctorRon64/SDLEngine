#pragma once
#include "Rigidbody.h"

class RigidBody;

class Collidable {
protected:
	RigidBody* rb = nullptr;

public:
	explicit Collidable(RigidBody* _rb)
		: rb(_rb) {
		CollisionManager::Instance().Register(rb, this);
	}

	virtual ~Collidable() {
		CollisionManager::Instance().Unregister(this);
	}

	virtual void OnCollision(Collidable* other) = 0;
};