#pragma once
#include "Enemy.h"

class Boss : public Enemy {
protected:
	int phase = 0;
	bool invulnerable = false;
	void OnDeath() override {
		WaveManager::GetInstance()->SetBossActive(false);
		Enemy::OnDeath();
	}

public:
	Boss(
		const std::string& texture,
		Vector2 spawnPos,
		Vector2 size,
		int maxHp
	)
		: Enemy(texture, spawnPos, size) {}

	virtual void Update() override {
		UpdatePhase();
		Enemy::Update();
	}

	virtual void UpdatePhase() = 0;

	void TakeDamage(int dmg) override {
		if(invulnerable) return;
		Enemy::TakeDamage(dmg);
	}
};
