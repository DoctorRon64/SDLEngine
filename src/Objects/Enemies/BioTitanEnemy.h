#pragma once
#include "../custom/Enemy.h"
#include "../custom/Bullet.h"

class BioTitanEnemy : public Enemy {
private:
	float burstTimer = 0.f;
	float burstCooldown = 1.5f;
	float bulletSpeed = 220.f;

public:
	BioTitanEnemy(Vector2 spawn)
		: Enemy(ENEMY_BIO_TITAN_SPRITE_PATH, spawn, { 64, 64 }) {
		InitHp(500);
		transform->scale = { 4.f, 4.f };
	}

	void Update() override {
		float dt = TimeManager::GetInstance()->GetDeltaTime();
		burstTimer -= dt;
		if(burstTimer <= 0.f) {
			ShootBurst();
			burstTimer = burstCooldown;
		}

		Enemy::Update();
	}

private:
	void ShootBurst() {
		const int minShots = 3;
		const int maxShots = 7;
		int count = Randomness::Range(minShots, maxShots);

		std::array<float, 7> angles = { -60.f, -40.f, -20.f, 0.f, 20.f, 40.f, 60.f };
		std::shuffle(angles.begin(), angles.end(), Randomness::Generator());

		Vector2 origin = transform->position;
		for(int i = 0; i < count; ++i) {
			float rad = angles[i] * 3.14159265f / 180.0f;
			Vector2 dir = { cos(rad), sin(rad) };
			dir.Normalize();
			dir.x = -fabs(dir.x);

			Bullet* b = new Bullet(false, ENEMY_BULLET_SPRITE_PATH);
			b->GetTransform()->position = origin;
			b->GetRigidBody()->SetVelocity(dir * bulletSpeed);
			SpawnManager::Instance().SpawnObject(b);
		}
	}
};
