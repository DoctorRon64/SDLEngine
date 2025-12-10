#pragma once
#include "../Image.h"
#include "./baseEnemy.h"

class bullet : public Image {
public:
	bullet(std::string _name = "res/bullet.png", Vector2 _pos = Vector2(0.f, 0.f), Vector2 _size = Vector2(400.f, 400.f))
		: Image(_name, _pos, _size) {
		transform->scale = Vector2(0.5f, 0.5f);
		transform->rotation = 90.f;

		std::cout << "Bullet Position: " << transform->position.x << ", " << transform->position.y << std::endl;
		std::cout << "Bullet Scale: " << transform->scale.x << ", " << transform->scale.y << std::endl;

		rbComp->SetAngularDrag(0.0f);
		rbComp->SetLinearDrag(0.0f);
		rbComp->AddCollider(new AABB(_pos, _size));

		rbComp->SetVelocity(Vector2(bulletSpeed, 0.f));
	}

	void Update() override {
		Image::Update();

		if(transform->position.x > renderManager->WINDOW_WIDTH || transform->position.x < -50) {
			Destroy();
			std::cout << this << "object has been dleteted" << std::endl;
			return;
		}
	}
private:
	float bulletSpeed = 350.f;
};
