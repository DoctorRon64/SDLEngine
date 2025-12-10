#pragma once
#include "../Image.h"
#include "./baseEnemy.h"
#include "./bullet.h"

class Player : public Image {
public:
	Player(std::string _name = "res/man.png") :
		Image(_name, Vector2(0.f, 0.f), Vector2(992.f, 1542.f)) {
		//Vector2 middle = Vector2((float)renderManager->WINDOW_WIDTH / 2, (float)renderManager->WINDOW_HEIGHT / 2);
		transform->position = Vector2(0.f, 0.f);
		transform->scale = Vector2(2.f, 2.f);

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
		else if(inputManager->GetEvent(SDLK_SPACE, DOWN)) {
			Shoot();
		}

		Object::Update();
	}

	void Shoot() {
		const std::string tex = "res/bullet.png";
		auto b = new bullet();

		b->SetLayer(20);
		Vector2 pos = transform->position + (textureSize / 4);
		b->GetTransform()->position = pos;

		spawnerManager.SpawnObject(b);
	}
};
