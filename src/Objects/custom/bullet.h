#pragma once
#include "../Image.h"
#include "./Enemy.h"

class Bullet : public Image {
public:
	Bullet(std::string _name = "res/bullet.png", Vector2 _pos = Vector2(0.f, 0.f), Vector2 _size = Vector2(400.f, 400.f))
		: Image(_name, _pos, _size) {
		transform->scale = Vector2(0.5f, 0.5f);
		transform->rotation = 90.f;

		rbComp->SetAngularDrag(0.0f);
		rbComp->SetLinearDrag(0.0f);
		rbComp->AddCollider(new AABB(_pos, _size));

		rbComp->SetVelocity(Vector2(bulletSpeed, 0.f));
	}

	void Update() override {
		lifeTime -= timeManager->GetDeltaTime();
		if(lifeTime <= 0.0f) {
			Destroy();
			return;
		}

		if(transform->position.x > renderManager->WINDOW_WIDTH || transform->position.x < -50) {
			Destroy();
			return;
		}

		Image::Update();
	}
private:
	float bulletSpeed = 350.f;
	float lifeTime = 2.0f;
};
