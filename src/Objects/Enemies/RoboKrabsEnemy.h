#pragma once
#include "../custom/Enemy.h"
#include "../custom/Player.h"

class RoboKrabsEnemy : public Enemy {
private:
	float jumpTimer = 0.f;
	float jumpCooldown = 0.f;
	float jumpSpeed = 220.f;
	bool jumping = false;
	Vector2 jumpTarget;

public:
	RoboKrabsEnemy(Vector2 spawn)
		: Enemy(ENEMY_ROBO_KRABS_SPRITE_PATH, spawn, { 32, 32 }) {
		bool fromTop = (Randomness::Range(0, 1) == 0);
		float x = Randomness::Range(0.f, RenderManager::GetInstance()->WINDOW_WIDTH);
		float y = fromTop ? 0.f : (RenderManager::GetInstance()->WINDOW_HEIGHT - transform->GetSize().y);
		transform->position = { x, y };
		jumpCooldown = Randomness::Range(3.f, 5.f);
		InitHp(35);
	}

	const std::string& GetDeathSfx() const override { return SFX_ENEMY_ROBO_KRABS_DEATH_PATH; }

	void Update() override {
		float dt = TimeManager::GetInstance()->GetDeltaTime();

		if(jumping) {
			Vector2 dir = jumpTarget - transform->position;
			if(dir.Length() < 5.f) {
				jumping = false;
				jumpTimer = 0.f;
				jumpCooldown = Randomness::Range(3.f, 5.f);
			}
			else {
				dir.Normalize();
				transform->position += dir * jumpSpeed * dt;
			}
		}
		else {
			jumpTimer += dt;
			if(jumpTimer >= jumpCooldown) {
				jumping = true;
				Player* player = Player::GetInstance();
				jumpTarget = player ? player->GetTransform()->position : transform->position;
			}
		}

		Enemy::Update();
	}
};
