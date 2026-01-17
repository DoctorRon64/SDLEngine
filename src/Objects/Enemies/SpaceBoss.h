#pragma once
#include "../custom/Boss.h"
#include "../custom/Bullet.h"

class SpaceBoss : public Boss {
private:
	float burstTimer = 0.f;
	float burstCooldown = 1.2f;
	float bulletSpeed = 240.f;
	float bobTimer = 0.f;
	float bobAmplitude = 40.f;
	float baseY = 0.f;

public:
	SpaceBoss(Vector2 spawn)
		: Boss(ENEMY_SPACE_BOSS_SPRITE_PATH, spawn, { 64, 64 }, 300) {
		transform->position = spawn;
		baseY = spawn.y;
		InitHp(300);
	}

	void UpdatePhase() override {
		float dt = TimeManager::GetInstance()->GetDeltaTime();

		bobTimer += dt;
		transform->position.y = baseY + sin(bobTimer) * bobAmplitude;

		burstTimer -= dt;
		if(burstTimer <= 0.f) {
			ShootBurst();
			burstTimer = burstCooldown;
		}
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

			Bullet* b = new Bullet(false);
			b->GetTransform()->position = origin;
			b->GetRigidBody()->SetVelocity(dir * bulletSpeed);
			SpawnManager::Instance().SpawnObject(b);
		}
	}
};
