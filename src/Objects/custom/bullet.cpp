#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(std::string _name, Vector2 _pos, Vector2 _size, bool _isPlayer)
	: Image(_name, _pos, _size), isPlayerBullet(_isPlayer) {
	rbComp->AddCollider(new AABB(_pos, _size));
	rbComp->SetVelocity(Vector2(bulletSpeed, 0.f));

	transform->scale = { .1f, .1f };
	transform->rotation = (_isPlayer) ? 90 : -90;

	CollisionManager::Instance().Register(rbComp, this);
}

Bullet::~Bullet() {
	CollisionManager::Instance().Unregister(this);
}

void Bullet::Update() {
	Image::Update();
	if(transform->position.x > RenderManager::GetInstance()->WINDOW_WIDTH || transform->position.x < -50) {
		Destroy();
	}
}

void Bullet::OnCollision(Object* other) {
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