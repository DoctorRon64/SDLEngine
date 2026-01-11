#pragma once

class RigidBody;
class Collidable;

class CollisionManager {
public:
	static CollisionManager& Instance() {
		static CollisionManager instance;
		return instance;
	}

	void CheckCollisions();
	void Register(RigidBody* rb, Collidable* c);
	void Unregister(Collidable* c);

private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;

	struct CollidableEntry {
		RigidBody* rb;
		Collidable* collidable;
	};

	std::vector<CollidableEntry> collidables;
};
