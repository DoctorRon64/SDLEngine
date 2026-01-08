#pragma once
#include "../Actor.h"

enum class EnemyState {
	STAY,
	SIMPLE_MOVE,
	CIRCLE_MOVE,
	CHASE
};

class Enemy : public Actor {
protected:
	EnemyState state = EnemyState::STAY;
	float stateTimer = 0.f;

	int hp = 1;
	int scoreValue = 100;
	float speed = 50.f;

	Vector2 velocity = { 0, 0 };

public:
	Enemy(
		const std::string& texture,
		Vector2 spawnPos,
		Vector2 size
	) : Actor(texture, { 0,0 }, size) {
		transform->position = spawnPos;
		transform->scale = { 2.f, 2.f };

		rbComp->AddCollider(new AABB(transform->position, transform->GetSize()));
		rbComp->SetLinearDrag(0.0f);
	}

	virtual void Update() override {
		float dt = TimeManager::GetInstance()->GetDeltaTime();
		stateTimer += dt;

		UpdateState(dt);
		Image::Update();
	}

	virtual void TakeDamage(int dmg) {
		hp -= dmg;
		if(hp <= 0) {
			OnDeath();
		}
	}

	virtual void OnDeath() {
		ScoreManager::GetInstance()->AddScore(scoreValue);
		Destroy();
	}

protected:
	float shootCooldown = 1.f;
	float shootTimer = 0.f;

	void UpdateShooting(float dt) {
		shootTimer -= dt;
		if(shootTimer <= 0.f) {
			Shoot();
			shootTimer = shootCooldown;
		}
	}

	virtual void Shoot() {
		// Default enemy does not shoot
	}
	virtual void UpdateState(float dt) = 0;
};