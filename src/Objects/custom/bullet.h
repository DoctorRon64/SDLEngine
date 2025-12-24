#pragma once
#include "Enemy.h"
#include "Player.h"

class Bullet : public Image {
public:
	bool isPlayerBullet = true;

	Bullet(std::string _name = "res/bullet.png", Vector2 _pos = Vector2(0.f, 0.f), Vector2 _size = Vector2(40.f, 40.f)), bool _isPlayer = true)
	: Image(_name, _pos, _size), isPlayerBullet(_isPlayer)  {
		rbComp->AddCollider(new AABB(_pos, Vector2(40.f, 40.f)));
		rbComp->SetVelocity(Vector2(bulletSpeed, 0.f));

		CollisionManager::Instance().Register(rbComp, this, isPlayerBullet);
	}

	~Bullet() {
		CollisionManager::Instance().Unregister(this);
	}

	void Update() override {
		Image::Update();
		if(transform->position.x > RenderManager::GetInstance()->WINDOW_WIDTH || transform->position.x < -50) {
			Destroy();
		}
	}

private:
	void CheckCollision() {
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

	float bulletSpeed = 350.f;
};
