#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(bool _isPlayer, std::string _name, Vector2 _pos, Vector2 _size)
	: Image(_name, _pos, _size),
	Collidable(this, rbComp),
	isPlayerBullet(_isPlayer) {
	rbComp->AddCollider(new AABB(_pos, _size));
	rbComp->SetVelocity(isPlayerBullet ? Vector2(bulletSpeed, 0.f) : Vector2(-bulletSpeed, 0.f));

	transform->scale = { 0.1f, 0.1f };
	transform->rotation = isPlayerBullet ? 90.f : -90.f;
}

void Bullet::Update() {
	Image::Update();

	if(transform->position.x > RenderManager::GetInstance()->WINDOW_WIDTH ||
		transform->position.x < -50.f) {
		Destroy();
	}
}

void Bullet::OnCollision(Object* other) {
	if(isPlayerBullet) {
		if(auto enemy = dynamic_cast<Enemy*>(other)) {
			std::cout << enemy << "enemy1" << std::endl;
			enemy->TakeDamage(10);
			Destroy();
		}
	}
	else {
		if(auto player = dynamic_cast<Player*>(other)) {
			std::cout << player << "player1" << std::endl;
			player->DecrementLives(1);
			Destroy();
		}
	}
}