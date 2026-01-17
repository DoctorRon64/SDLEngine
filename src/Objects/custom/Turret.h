#pragma once
#include "../Actor.h"
#include "./bullet.h"

class Turret : public Actor {
public:
	Turret(Vector2 spawnPos) : Actor(TURRET_SPRITE_PATH, Vector2(0.f, 0.f), Vector2(32, 32)) {
		transform->position = spawnPos;
		transform->scale = { 2.f, 2.f };
		SetLayer(20);
	}

	void Shoot() {
		Bullet* b = new Bullet(true, BULLET_SPRITE_PATH, transform->position);
		b->SetLayer(20);
		SpawnManager::Instance().SpawnObject(b);
	}

	void ApplyPlayerMovement(float deltaX) {
		transform->rotation += deltaX * TURRET_ROTATION_DEG_PER_X;
	}

	virtual void OnCollision(Collidable* other) override {}
};
