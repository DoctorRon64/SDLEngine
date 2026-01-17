#pragma once
#include "../custom/TrailBullet.h"
#include "../custom/Enemy.h"
#include "states/CircleMoveState.h"

class CirclerEnemy : public Enemy {
private:
	float trailTimer = 0.f;
	float trailInterval = 0.1f;
	float trailLife = 1.5f;

public:
	CirclerEnemy(Vector2 spawn)
		: Enemy(ENEMY_CIRCLER_SPRITE_PATH, spawn, { 32, 32 }) {
		stateManager.AddState(new CircleMoveState(&transform->position, spawn, 100.f, 90.f, 3));
		InitHp(35);
	}

	void Update() override {
		float dt = TimeManager::GetInstance()->GetDeltaTime();
		Enemy::Update();

		trailTimer += dt;
		if(trailTimer >= trailInterval) {
			SpawnTrailBullet();
			trailTimer = 0.f;
		}
	}

	void SpawnTrailBullet() {
		TrailBullet* b = new TrailBullet(transform->position, trailLife);
		SpawnManager::Instance().SpawnObject(b);
	}
};
