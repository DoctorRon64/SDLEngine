#pragma once

class RigidBody;
class Object;

class CollisionManager {
public:
	static CollisionManager& Instance() {
		static CollisionManager instance;
		return instance;
	}

	void Register(RigidBody* rb, Object* owner);
	void Unregister(Object* owner);

	void CheckCollisions();

private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;

	struct CollidableEntry {
		RigidBody* rb;
		Object* owner;
	};

	std::vector<CollidableEntry> collidables;
};
