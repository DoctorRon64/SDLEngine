#include "pch.h"
#include "CollisionManager.h"
#include "Components/RigidBody.h"
#include "Objects/Object.h"

void CollisionManager::Register(RigidBody* rb, Object* owner) {
	collidables.push_back({ rb, owner });
}

void CollisionManager::Unregister(Object* owner) {
	collidables.erase(
		std::remove_if(
			collidables.begin(),
			collidables.end(),
			[owner](const Collidable& c) {
		return c.owner == owner;
	}
		),
		collidables.end()
	);
}

void CollisionManager::CheckCollisions() {
	for(size_t i = 0; i < collidables.size(); ++i) {
		for(size_t j = i + 1; j < collidables.size(); ++j) {
			Collidable& a = collidables[i];
			Collidable& b = collidables[j];

			if(!a.rb || !b.rb) continue;

			if(a.rb->CheckCollision(b.rb)) {
				// notify both objects
				a.owner->OnCollision(b.owner);
				b.owner->OnCollision(a.owner);
			}
		}
	}
}