#include "pch.h"
#include "Components/RigidBody.h"
#include "Objects/Object.h"
#include "Managers/RenderManager.h"
#include "Math/AABB.h"

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

void CollisionManager::ToggleDebug() {
	debugDraw = !debugDraw;
}

void CollisionManager::RenderDebug() {
	if(!debugDraw) return;

	SDL_Renderer* renderer = RenderManager::GetInstance()->GetRenderer();
	Uint8 prevR = 0, prevG = 0, prevB = 0, prevA = 0;
	SDL_GetRenderDrawColor(renderer, &prevR, &prevG, &prevB, &prevA);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	for(const CollidableEntry& entry : collidables) {
		for(AABB* box : entry.rb->GetColliders()) {
			Vector2 topLeft = box->GetTopLeft();
			Vector2 size = box->GetSize();
			SDL_FRect rect = { topLeft.x, topLeft.y, size.x, size.y };
			SDL_RenderRect(renderer, &rect);
		}
	}

	SDL_SetRenderDrawColor(renderer, prevR, prevG, prevB, prevA);
}
