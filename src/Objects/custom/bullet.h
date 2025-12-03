#pragma once
#include "../ImageObject.h"
#include "./baseEnemy.h"

class bullet : public ImageObject {
public:

	bullet(std::string _name = "res/missing.png",
		   Vector2 _pos = Vector2(0.f, 0.f),
		   Vector2 _size = Vector2(30.f, 10.f))
		: ImageObject(_name, _pos, _size) {
		rbComp->SetVelocity(Vector2(650.f, 0.f));

		transform->rotation = 90;

		rbComp->SetAngularDrag(0.0f);
		rbComp->SetLinearDrag(0.0f);
		rbComp->AddCollider(new AABB(_pos, _size));
	}

	void Update() override {
		ImageObject::Update();

		UpdateCollider();

		if(transform->position.x > renderManager->WINDOW_WIDTH || transform->position.x < -50) {
			Destroy();
			std::cout << this << "object has been dleteted" << std::endl;
			return;
		}
	}

private:

	void UpdateCollider() {
		for(AABB* c : rbComp->GetColliders()) {
			c->SetTopLeft(transform->position);
		}
	}
};
