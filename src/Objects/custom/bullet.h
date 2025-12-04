#pragma once
#include "../Image.h"
#include "./baseEnemy.h"

class bullet : public Image {
public:
	bullet(std::string _name = "res/bullet.png", Vector2 _pos = Vector2(0.f, 0.f), Vector2 _size = Vector2(400.f, 400.f))
		: Image(_name, _pos, _size) {
		//rbComp->SetVelocity(Vector2(1.f, 0.f));

		transform->position = _pos;
		transform->scale = Vector2(2.f, 2.f);
		transform->rotation = 90;

		//rbComp->SetAngularDrag(0.0f);
		//rbComp->SetLinearDrag(0.0f);
		//rbComp->AddCollider(new AABB(_pos, _size));
		std::cout << transform->position.x << " " << transform->position.y << " transform pos" << std::endl;
		std::cout << _pos.x << " " << _pos.y << " mee gegeven pos" << std::endl;
	}

	void Update() override {
		Image::Update();

		/*UpdateCollider();

		if(transform->position.x > renderManager->WINDOW_WIDTH || transform->position.x < -50) {
			Destroy();
			std::cout << this << "object has been dleteted" << std::endl;
			return;
		}*/
	}
};
