#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(std::string _name, Vector2 _pos, Vector2 _size, bool _isPlayer)
	: Image(_name, _pos, _size), isPlayerBullet(_isPlayer) {
	rbComp->AddCollider(new AABB(_pos, _size));
	rbComp->SetVelocity(Vector2(bulletSpeed, 0.f));

	transform->scale = { .1f, .1f };
	transform->rotation = (_isPlayer) ? 90 : -90;

	CollisionManager::Instance().Register(rbComp, this, isPlayerBullet);
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

void Bullet::CheckCollision() {
	std::queue<Object*> objs = SpawnManager::Instance().GetSpawnedObjects(); // copy queue
	while(!objs.empty()) {
		Object* obj = objs.front();
		objs.pop();

		if(Enemy* enemy = dynamic_cast<Enemy*>(obj)) {
			if(isPlayerBullet && rbComp->CheckCollision(enemy->GetRigidBody())) {
				enemy->TakeDamage(10);
				Destroy();
				break;
			}
		}
		else if(Player* player = dynamic_cast<Player*>(obj)) {
			if(!isPlayerBullet && rbComp->CheckCollision(player->GetRigidBody())) {
				player->DecrementLives(1);
				Destroy();
				break;
			}
		}
	}
}