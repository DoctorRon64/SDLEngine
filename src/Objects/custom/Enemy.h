#pragma once
#include "../../managers/EnemyStateManager.h"
#include "../Actor.h"

class Enemy : public Actor {
protected:
	EnemyStateManager stateManager;

	float stateTimer = 0.f;
	int scoreValue = 100;
	float speed = 50.f;
	float shootCooldown = 1.f;
	float shootTimer = 0.f;

	Vector2 velocity = { 0, 0 };

	virtual void OnDeath() override;

	void UpdateShooting(float dt);
	virtual void UpdateState(float dt) = 0;
	virtual void Shoot() {}

	void ClampToScreen();

public:
	Enemy(
		const std::string& texture,
		Vector2 spawnPos,
		Vector2 size
	);
	virtual void Update() override;
};