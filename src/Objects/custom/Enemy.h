#pragma once
#include "../../managers/EnemyStateManager.h"
#include "../Actor.h"

class Enemy : public Actor {
protected:
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

protected:
	EnemyStateManager stateManager;

	float shootCooldown = 1.f;
	float shootTimer = 0.f;

	void UpdateShooting(float dt);

	virtual void Shoot() {}
	virtual void UpdateState(float dt) = 0;

	void ClampToScreen();
};