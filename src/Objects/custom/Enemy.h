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

	int scoreValue = 100;
	float speed = 50.f;

	Vector2 velocity = { 0, 0 };

	virtual void OnDeath() override;

public:
	Enemy(
		const std::string& texture,
		Vector2 spawnPos,
		Vector2 size
	);
	virtual void Update() override;
	virtual void OnCollision(Collidable* other) override {}

protected:
	float shootCooldown = 1.f;
	float shootTimer = 0.f;

	void UpdateShooting(float dt);

	virtual void Shoot() {}
	virtual void UpdateState(float dt) = 0;
};