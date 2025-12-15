#pragma once
#include "./Enemy.h"

class HorizontalMedusa : public Enemy {
public:
	//HorizontalMedusa() {
	//	//speed = RandomRange(10, 50);
	//	//if(rand() % 2) speed *= -1;
	//}

	HorizontalMedusa(std::string _name = "res/evil-woman.png",
		Vector2 _pos = Vector2(0.f, 0.f),
		Vector2 _size = Vector2(1024.f, 1303.f)) : Enemy(_name, _pos, _size) {
		Vector2 randomPosition = Vector2(500, 500);
		transform->position = randomPosition;
		transform->scale = Vector2(2.5f, 2.5f);

		rbComp->SetAngularDrag(0.5f);
		rbComp->SetLinearDrag(0.5f);
		rbComp->AddCollider(new AABB(_pos, _size));
	}

	virtual void Update() override {
		//TODO
		//rbComp->AddForce(Vector2(speed, 0));
	}
};
