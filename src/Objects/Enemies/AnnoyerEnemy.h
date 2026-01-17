#pragma once
#include "../custom/Enemy.h"
#include "../custom/Player.h"

class AnnoyerEnemy : public Enemy {
private:
	enum class Phase {
		ENTER,
		HOVER,
		LUNGE
	};

	Phase phase = Phase::ENTER;
	float hoverTimer = 0.f;
	float hoverDuration = 0.6f;
	float moveSpeed = 160.f;
	float lungeSpeed = 260.f;
	Vector2 entryPoint;
	Vector2 lungeTarget;

public:
	AnnoyerEnemy(Vector2 spawn)
		: Enemy(ENEMY_ANNOYER_SPRITE_PATH, spawn, { 32, 32 }) {
		float startX = RenderManager::GetInstance()->WINDOW_WIDTH + transform->GetSize().x;
		float startY = Randomness::Range(0.f, RenderManager::GetInstance()->WINDOW_HEIGHT);
		transform->position = { startX, startY };

		entryPoint = { RenderManager::GetInstance()->WINDOW_WIDTH * 0.7f, startY };
		InitHp(15);
	}

	void Update() override {
		float dt = TimeManager::GetInstance()->GetDeltaTime();

		if(phase == Phase::ENTER) {
			MoveTowards(entryPoint, moveSpeed, dt);
			if((transform->position - entryPoint).Length() < 5.f) {
				phase = Phase::HOVER;
				hoverTimer = 0.f;
			}
		}
		else if(phase == Phase::HOVER) {
			hoverTimer += dt;
			if(hoverTimer >= hoverDuration) {
				Player* player = Player::GetInstance();
				lungeTarget = player ? player->GetTransform()->position : transform->position;
				phase = Phase::LUNGE;
			}
		}
		else {
			MoveTowards(lungeTarget, lungeSpeed, dt);
		}

		Enemy::Update();
	}

private:
	void MoveTowards(const Vector2& target, float speed, float dt) {
		Vector2 dir = target - transform->position;
		float dist = dir.Length();
		if(dist < 1.f) return;
		dir.Normalize();
		transform->position += dir * speed * dt;
	}
};
