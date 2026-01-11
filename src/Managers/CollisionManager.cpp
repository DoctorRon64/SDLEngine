#include "pch.h"
#include "Components/RigidBody.h"
#include "Objects/Object.h"

void CollisionManager::CheckCollisions() {
	for(size_t i = 0; i < collidables.size(); i++) {
		for(size_t j = i + 1; j < collidables.size(); j++) {
			auto& a = collidables[i];
			auto& b = collidables[j];

			if(!a.rb->CheckCollision(b.rb))
				continue;

			a.collidable->OnCollision(b.collidable);
			b.collidable->OnCollision(a.collidable);
		}
	}
}

void CollisionManager::Register(RigidBody* rb, Collidable* c) {
	collidables.push_back({ rb, c });
}

void CollisionManager::Unregister(Collidable* c) {
	collidables.erase(
		std::remove_if(
			collidables.begin(),
			collidables.end(),
			[c](const CollidableEntry& e) {
		return e.collidable == c;
	}
		),
		collidables.end()
	);
}