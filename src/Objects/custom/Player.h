#pragma once
#include "../../components/Animator.h"
#include "../Image.h"
#include "./Bullet.h"

class Player : public Image {
public:
	Player(std::string _name = "res/player_sprite.png") :
		Image(_name, Vector2(0.f, 0.f), Vector2(350.f, 150.f)) {
		transform->position = Vector2(0.f, 0.f);
		transform->scale = Vector2(2.f, 2.f);

		rbComp->SetAngularDrag(0.5f);
		rbComp->SetLinearDrag(0.5f);

		//Animation idle{ 7, {350,150}, 0.12f, true, 0 };
		//animator = new Animator(dynamic_cast<ImageRenderer*>(renderer), idle);
	}

	virtual void Update() override {
		float dt = timeManager->GetDeltaTime();
		shootTimer -= dt;

		HandleMovement();
		HandleShooting();
		Image::Update();

		ClampToScreen();
		//animator->Update(dt);
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
		Vector2 pos = Vector2(transform->position.x + (textureSize.x / 2), transform->position.y + (textureSize.y / 2));

		b->GetTransform()->position = pos;

		spawnerManager.SpawnObject(b);
	}

private:
	void ClampToScreen() {
		float w = textureSize.x * transform->scale.x;
		float h = textureSize.y * transform->scale.y;

		if(transform->position.x <= 0 || transform->position.x >= renderManager->WINDOW_WIDTH - w) {
			rbComp->SetVelocity({ 0, rbComp->GetVelocity().y });
		}

		if(transform->position.y <= 0 || transform->position.y >= renderManager->WINDOW_HEIGHT - h) {
			rbComp->SetVelocity({ rbComp->GetVelocity().x, 0 });
		}
	}

	float shootCooldown = 0.2f;
	float shootTimer = 0.0f;
	int shields = 100;
	bool invulnerable = false;
	Animator* animator = nullptr;
};
