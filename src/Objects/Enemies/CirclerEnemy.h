#pragma once
#include "../custom/Bullet.h"
#include "../custom/Enemy.h"
#include "states/CircleMoveState.h"

class CirclerEnemy : public Enemy {
private:
	float shootTimer = 0.f;

public:
	CirclerEnemy(Vector2 spawn)
		: Enemy(ENEMY_CIRCLER_SPRITE_PATH, spawn, { 32, 32 }) {
		stateManager.AddState(new CircleMoveState(&transform->position, spawn, 100.f, 90.f, 3));
		InitHp(6);
	}

	void Update() override {
		float dt = TimeManager::GetInstance()->GetDeltaTime();
		Enemy::Update();

		shootTimer += dt;
		if(shootTimer >= 0.3f) {
			ShootBullet();
			shootTimer = 0.f;
		}
	}

	void ShootBullet() {
		Vector2 dir(1.f, 0.f);
		Bullet* b = new Bullet(false, BULLET_SPRITE_PATH, transform->position, dir * 200.f);
		SpawnManager::Instance().SpawnObject(b);
	}
};
