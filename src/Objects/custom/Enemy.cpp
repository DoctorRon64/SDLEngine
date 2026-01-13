#include "pch.h"
#include "Enemy.h"

void Enemy::OnDeath() {
	WaveManager::GetInstance()->UnregisterEnemy();
	ScoreManager::GetInstance()->AddScore(scoreValue);
	AudioManager::GetInstance()->PlaySound(SFX_HURT_ENEMY_PATH);
	Actor::OnDeath();
}

Enemy::Enemy(const std::string& texture, Vector2 spawnPos, Vector2 size) : Actor(texture, { 0,0 }, size) {
	transform->position = spawnPos;
	transform->scale = { 2.f, 2.f };

	rbComp->AddCollider(new AABB(transform->position * 2, transform->GetSize()));
	rbComp->SetLinearDrag(0.0f);
	InitHp(1);

	WaveManager::GetInstance()->RegisterEnemy();
}

void Enemy::Update() {
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	stateTimer += dt;

	stateManager.Update(dt);
	UpdateState(dt);
	ClampToScreen();
	Image::Update();
}

void Enemy::UpdateShooting(float dt) {
	shootTimer -= dt;
	if(shootTimer <= 0.f) {
		Shoot();
		shootTimer = shootCooldown;
	}
}