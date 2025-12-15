#pragma once
#include "../Image.h"
#include "./Bullet.h"

class Player : public Image {
public:
	Player(std::string _name = "res/man.png") :
		Image(_name, Vector2(0.f, 0.f), Vector2(992.f, 1542.f)) {
		transform->position = Vector2(0.f, 0.f);
		transform->scale = Vector2(2.f, 2.f);

		rbComp->SetAngularDrag(0.5f);
		rbComp->SetLinearDrag(0.5f);
	}

	virtual void Update() override {
		shootTimer -= timeManager->GetDeltaTime();

		HandleMovement();
		HandleShooting();

		Image::Update();
	}

	void HandleMovement() {
		if(inputManager->GetEvent(SDLK_W, HOLD)) {
			rbComp->AddForce(Vector2(0.0f, -300.0f));
		}
		if(inputManager->GetEvent(SDLK_S, HOLD)) {
			rbComp->AddForce(Vector2(0.0f, 300.0f));
		}
		if(inputManager->GetEvent(SDLK_A, HOLD)) {
			rbComp->AddForce(Vector2(-300.0f, 0.0f));
		}
		if(inputManager->GetEvent(SDLK_D, HOLD)) {
			rbComp->AddForce(Vector2(300.0f, 0.0f));
		}
		if(inputManager->GetEvent(SDLK_R, HOLD)) {
			rbComp->AddTorque(0.1f);
		}
	}

	void HandleShooting() {
		if(inputManager->GetEvent(SDLK_SPACE, DOWN) || inputManager->GetLeftClick()) {
			if(shootTimer <= 0.0f) {
				Shoot();
				shootTimer = shootCooldown;
			}
		}
	}

	void Shoot() {
		const std::string tex = "res/bullet.png";
		auto b = new Bullet();

		b->SetLayer(20);
		Vector2 pos = transform->position + (textureSize / 4);
		b->GetTransform()->position = pos;

		spawnerManager.SpawnObject(b);
	}

private:
	float shootCooldown = 0.2f;
	float shootTimer = 0.0f;
	int shields = 100;
	bool invulnerable = false;
};
