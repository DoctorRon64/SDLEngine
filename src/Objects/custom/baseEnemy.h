#pragma once
#include "../ImageObject.h"

class baseEnemy : public ImageObject {
public:
	baseEnemy(std::string _name = "res/missing.png", Vector2 _pos = Vector2(0.f, 0.f), Vector2 _size = Vector2(1024.f, 1303.f)) : ImageObject(_name, _pos, _size) {
		Vector2 randomPosition = Vector2(
			static_cast<float>(rand() % renderManager->WINDOW_WIDTH),
			static_cast<float>(rand() % renderManager->WINDOW_HEIGHT)
		);
		transform->position = randomPosition;
		transform->scale = Vector2(2.f, 2.f);

		rbComp->SetAngularDrag(0.5f);
		rbComp->SetLinearDrag(0.5f);
	}
};