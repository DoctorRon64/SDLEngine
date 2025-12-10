#pragma once
#include "../Image.h"

class baseEnemy : public Image {
public:
	baseEnemy(std::string _name = "res/evil-woman.png", Vector2 _pos = Vector2(0.f, 0.f), Vector2 _size = Vector2(1024.f, 1303.f)) : Image(_name, _pos, _size) {
		Vector2 randomPosition = Vector2(500, 500);
		transform->position = randomPosition;
		transform->scale = Vector2(2.5f, 2.5f);

		rbComp->SetAngularDrag(0.5f);
		rbComp->SetLinearDrag(0.5f);
		rbComp->AddCollider(new AABB(_pos, _size));
	}
};