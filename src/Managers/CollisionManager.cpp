#include "pch.h"
#include "CollisionManager.h"

#include "../objects/custom/Enemy.h"
#include "../objects/custom/Player.h"

void CollisionManager::Register(RigidBody* rb, Object* owner, bool isPlayer) {
	collidables.push_back({ rb, owner, isPlayer });
}

void CollisionManager::Unregister(Object* owner) {
	collidables.erase(
		std::remove_if(collidables.begin(), collidables.end(),
			[owner](const Collidable& c) { return c.owner == owner; }),
		collidables.end()
	);
}

void CollisionManager::CheckCollisions() {
	for(auto& a : collidables) {
		for(auto& b : collidables) {
			if(a.owner == b.owner) continue;
			// player bullet hits enemy
			if(a.isPlayer && !b.isPlayer) {
				if(a.rb->CheckCollision(b.rb)) {
					Enemy* enemy = dynamic_cast<Enemy*>(b.owner);
					if(enemy) enemy->TakeDamage(10);
					a.owner->Destroy();
				}
			}
			// enemy bullet hits player
			if(!a.isPlayer && b.isPlayer) {
				if(a.rb->CheckCollision(b.rb)) {
					Player* player = dynamic_cast<Player*>(b.owner);
					if(player) player->DecrementLives(1);
					a.owner->Destroy();
				}
			}
		}
	}
}