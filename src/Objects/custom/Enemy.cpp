#include "pch.h"
#include "Enemy.h"

void Enemy::OnDeath() {
	WaveManager::GetInstance()->UnregisterEnemy();
	ScoreManager::GetInstance()->AddScore(scoreValue);
	AudioManager::GetInstance()->PlaySound(SFX_HURT_ENEMY_PATH);
	Actor::OnDeath();
}

Enemy::Enemy(const std::string& texture, Vector2 spawnPos, Vector2 size)
	: Actor(texture, Vector2(0.f, 0.f), size) {
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
	UpdateShooting(dt);

	Image::Update();
	DespawnIfOutOfScreen();
}

void Enemy::DespawnIfOutOfScreen() {
	auto* rm = RenderManager::GetInstance();
	Vector2 p = transform->position;
	Vector2 s = transform->GetSize();

	if(p.x + s.x < 0 || p.x > rm->WINDOW_WIDTH ||
	   p.y + s.y < 0 || p.y > rm->WINDOW_HEIGHT) {
		Destroy();
		WaveManager::GetInstance()->UnregisterEnemy();
	}
}

void Enemy::UpdateShooting(float dt) {
	shootTimer -= dt;
	if(shootTimer <= 0.f) {
		Shoot();
		shootTimer = shootCooldown;
	}
}