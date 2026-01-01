#pragma once
#include "Rigidbody.h"

class RigidBody;
class Object;

class Collidable {
protected:
	RigidBody* rb = nullptr;
	Object* owner = nullptr;

public:
	Collidable(Object* _owner, RigidBody* _rb)
		: owner(_owner), rb(_rb) {
		CollisionManager::Instance().Register(rb, owner);
	}

	virtual ~Collidable() {
		CollisionManager::Instance().Unregister(owner);
	}
};