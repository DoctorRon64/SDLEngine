#pragma once
#include "../Actor.h"
#include "./bullet.h"

class Turret : public Actor {
public:
	Turret(Vector2 spawnPos) : Actor(TURRET_SPRITE_PATH, spawnPos, Vector2(32, 32)) {}

	void Shoot() {
		Bullet* b = new Bullet(true);
		b->SetLayer(20);
		b->GetTransform()->position = transform->position;
		SpawnManager::Instance().SpawnObject(b);
	}

	virtual void OnCollision(Collidable* other) override {}
};
