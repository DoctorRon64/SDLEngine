#pragma once
#pragma once
#include "../custom/Bullet.h"
#include "../custom/Enemy.h"

class CirclerEnemy : public Enemy {
private:
	float angle = 0.f;
	Vector2 circleCenter;
	float radius = 100.f;
	float shootTimer = 0.f;

public:
	CirclerEnemy(Vector2 spawn)
		: Enemy("res/enemies/circler_sprite.png", spawn, { 32, 32 }) {
		state = EnemyState::CIRCLE_MOVE;
		circleCenter = spawn;
	}

protected:
	void UpdateState(float dt) override {
		angle += 90.f * dt; // 90 degrees per second
		const float DEG2RAD = 3.14159265f / 180.0f;

		transform->position.x = circleCenter.x + cos(angle * DEG2RAD) * radius;
		transform->position.y = circleCenter.y + sin(angle * DEG2RAD) * radius;

		// Shoot bullets every 0.3 seconds
		shootTimer += dt;
		if(shootTimer >= 0.3f) {
			ShootBullet();
			shootTimer = 0.f;
		}
	}

	void ShootBullet() {
		Vector2 dir = Vector2(cos(angle * 3.14159265f / 180.0f),
							  sin(angle * 3.14159265f / 180.0f));
		Vector2 size = dir * 200;
		Bullet* b = new Bullet("res/bullet.png", transform->position, size);
		spawnManager.SpawnObject(b);
	}
};
