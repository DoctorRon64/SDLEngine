#pragma once
#include "../components/Rigidbody.h"
#include "../objects/Object.h"

class Enemy;
class Player;

class CollisionManager {
public:
	static CollisionManager& Instance() {
		static CollisionManager instance;
		return instance;
	}

	void Register(RigidBody* rb, Object* owner, bool isPlayer);
	void Unregister(Object* owner);
	void CheckCollisions();

private:
	struct Collidable {
		RigidBody* rb;
		Object* owner;
		bool isPlayer;
	};
	std::vector<Collidable> collidables;
};
