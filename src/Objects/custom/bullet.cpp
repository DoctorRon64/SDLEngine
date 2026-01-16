#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(bool _isPlayer, std::string _name, Vector2 _pos, Vector2 _size)
	: Image(_name, Vector2(0.f, 0.f), _size),
	Collidable(rbComp),
	isPlayerBullet(_isPlayer) {
	transform->position = _pos;
	rbComp->AddCollider(new AABB(_pos, _size));
	rbComp->SetVelocity(isPlayerBullet ? Vector2(bulletSpeed, 0.f) : Vector2(-bulletSpeed, 0.f));

	transform->scale = { 1.f, 1.f };
}

void Bullet::Update() {
	Image::Update();

	float x = transform->position.x;
	float w = RenderManager::GetInstance()->WINDOW_WIDTH;

	if(x > w || x < -transform->GetSize().x) {
		Destroy();
		AudioManager::GetInstance()->PlaySound(SFX_HURT_BULLET_PATH);
	}
}

void Bullet::OnCollision(Collidable* other) {
	if(isPlayerBullet) {
		if(auto enemy = dynamic_cast<Enemy*>(other)) {
			enemy->TakeDamage(10);
			Destroy();
		}
	}
	else {
		if(auto player = dynamic_cast<Player*>(other)) {
			player->DecrementLives(1);
			Destroy();
		}
	}
}
