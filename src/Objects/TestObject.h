#pragma once
#include "ImageObject.h"

class TestObject : public ImageObject {
public:
	TestObject() : ImageObject("res/ship.jpg", Vector2(0.f, 0.f), Vector2(306.f, 562.f)) {
		Vector2 randomPosition = Vector2(
			static_cast<float>(rand() % renderManager->WINDOW_WIDTH),
			static_cast<float>(rand() % renderManager->WINDOW_HEIGHT)
		);
		transform->position = randomPosition;
		transform->scale = Vector2(0.5f, 0.5f);
		transform->rotation = 30.f;
		transform->size = Vector2(306.f, 562.f);

		rbComp->SetAngularDrag(0.5f);
		rbComp->SetLinearDrag(0.5f);
	}

	virtual void Update() override {
		if(inputManager->GetEvent(SDLK_W, HOLD)) {
			rbComp->AddForce(Vector2(0.0f, -200.0f));
		}
		else if(inputManager->GetEvent(SDLK_S, HOLD)) {
			rbComp->AddForce(Vector2(0.0f, 200.0f));
		}
		else if(inputManager->GetEvent(SDLK_A, HOLD)) {
			rbComp->AddForce(Vector2(-200.0f, 0.0f));
		}
		else if(inputManager->GetEvent(SDLK_D, HOLD)) {
			rbComp->AddForce(Vector2(200.0f, 0.0f));
		}
		else if(inputManager->GetEvent(SDLK_R, HOLD)) {
			rbComp->AddTorque(0.1f);
		}

		Object::Update();
	}
};