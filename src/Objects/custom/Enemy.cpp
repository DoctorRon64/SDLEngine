#include "pch.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Managers/SpawnManager.h"

void Enemy::OnDeath() {
	WaveManager::GetInstance()->UnregisterEnemy();
	ScoreManager::GetInstance()->AddScore(scoreValue);
	AudioManager::GetInstance()->PlaySound(GetDeathSfx());
	Explosion* explosion = new Explosion();
	explosion->GetTransform()->position = { transform->position.x - 50, transform->position.y - 130 };
	SpawnManager::Instance().SpawnObject(explosion);
	Actor::OnDeath();
}

Enemy::Enemy(const std::string& texture, Vector2 spawnPos, Vector2 size)
	: Actor(texture, Vector2(0.f, 0.f), size) {
	transform->position = spawnPos;
	transform->scale = { 2.f, 2.f };

	rbComp->AddCollider(new AABB(transform->position, transform->GetSize()));
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
	KeepOnScreenVertical(0.0f);
	DespawnIfOutOfScreen();
}

void Enemy::DespawnIfOutOfScreen() {
	if(!AllowOffscreenDespawn()) return;

	auto* rm = RenderManager::GetInstance();
	Vector2 p = transform->position;
	Vector2 s = transform->GetSize();

	if(p.x + s.x < 0 || p.x > rm->WINDOW_WIDTH ||
	   p.y + s.y < 0 || p.y > rm->WINDOW_HEIGHT) {
		Destroy();
		WaveManager::GetInstance()->UnregisterEnemy();
	}
}

void Enemy::KeepOnScreen(float margin) {
	auto* rm = RenderManager::GetInstance();
	Vector2 size = transform->GetSize();

	float minX = -margin;
	float minY = -margin;
	float maxX = rm->WINDOW_WIDTH - size.x + margin;
	float maxY = rm->WINDOW_HEIGHT - size.y + margin;

	if(transform->position.x < minX) transform->position.x = minX;
	if(transform->position.y < minY) transform->position.y = minY;
	if(transform->position.x > maxX) transform->position.x = maxX;
	if(transform->position.y > maxY) transform->position.y = maxY;
}

void Enemy::KeepOnScreenVertical(float margin) {
	auto* rm = RenderManager::GetInstance();
	Vector2 size = transform->GetSize();

	float minY = -margin;
	float maxY = rm->WINDOW_HEIGHT - size.y + margin;

	if(transform->position.y < minY) transform->position.y = minY;
	if(transform->position.y > maxY) transform->position.y = maxY;
}

void Enemy::UpdateShooting(float dt) {
	shootTimer -= dt;
	if(shootTimer <= 0.f) {
		Shoot();
		shootTimer = shootCooldown;
	}
}
