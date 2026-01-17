#pragma once
#include "Bullet.h"

class TrailBullet : public Bullet {
private:
	float lifeTime;
	float timer = 0.f;

public:
	TrailBullet(Vector2 pos, float lifeSeconds)
		: Bullet(false, ENEMY_BULLET_SPRITE_PATH, pos, Vector2(16.f, 16.f)),
		lifeTime(lifeSeconds) {
		GetTransform()->position = pos;
		GetRigidBody()->SetVelocity({ 0.f, 0.f });
		GetRigidBody()->SetLinearDrag(0.f);
	}

	void Update() override {
		Bullet::Update();

		timer += TimeManager::GetInstance()->GetDeltaTime();
		if(timer >= lifeTime) {
			Destroy();
		}
	}
};
