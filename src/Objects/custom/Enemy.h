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
	virtual const std::string& GetDeathSfx() const { return SFX_HURT_ENEMY_PATH; }
	virtual bool AllowOffscreenDespawn() const { return true; }
	void KeepOnScreen(float margin);
	void KeepOnScreenVertical(float margin);

	void UpdateShooting(float dt);
	virtual void Shoot() {}
	virtual void Update() override;

	void DespawnIfOutOfScreen();

public:
	Enemy(const std::string& texture, Vector2 spawnPos, Vector2 size);
};
