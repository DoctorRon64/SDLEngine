#pragma once
#include "../Actor.h"
#include "./Bullet.h"
#include <Utils/config.h>

class Player : public Actor {

private:
	int lives = PLAYER_LIVES;

public:
	Player(std::string _path = "res/man.png") :
		Actor(_path, Vector2(0.f, 0.f), Vector2(992, 1542), PLAYER_HEALTH, 0) {
		transform->position = Vector2(0.f, 0.f);
		transform->scale = Vector2(.1f, .1f);

		rbComp->SetAngularDrag(0.5f);
		rbComp->SetLinearDrag(0.5f);
	}

	virtual void Update() override {
		float dt = timeManager->GetDeltaTime();
		shootTimer -= dt;

		HandleMovement();
		HandleShooting();
		Image::Update();

		ClampToScreen();

		std::cout << "transform pos:" << transform->position.x << " , " << transform->position.y << std::endl;
		std::cout << "destrect:" << renderer->GetDestinationRect().x << " , " << renderer->GetDestinationRect().y << "," << renderer->GetDestinationRect().w << "," << renderer->GetDestinationRect().h << "," << std::endl;
		std::cout << "sourcrect" << renderer->GetSourceRect().x << " , " << renderer->GetSourceRect().y << "," << renderer->GetSourceRect().w << "," << renderer->GetSourceRect().h << "," << std::endl;
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

		Vector2 pos = Vector2(transform->position.x, transform->position.y);

		b->GetTransform()->position = pos;

		spawnerManager.SpawnObject(b);
	}

	int GetLives() { return lives; }
	void SetLives(int _lives) { lives = _lives; }
	void IncrementLives(int amount) { lives += amount; }
	void DecrementLives(int amount) { lives -= amount; }

private:
	void ClampToScreen() {
		std::cout << "window: " << renderManager->WINDOW_WIDTH - transform->GetSize().x << " , " << renderManager->WINDOW_HEIGHT - transform->GetSize().y << std::endl;

		if(transform->position.x <= 0 || transform->position.x >= RenderManager::GetInstance()->WINDOW_WIDTH - transform->GetSize().x) {
			rbComp->SetVelocity({ 0, rbComp->GetVelocity().y });
		}

		if(transform->position.y <= 0 || transform->position.y >= renderManager->WINDOW_HEIGHT - transform->GetSize().y) {
			rbComp->SetVelocity({ rbComp->GetVelocity().x, 0 });
		}
	}

	float shootCooldown = 0.2f;
	float shootTimer = 0.0f;
	int shields = 100;
	bool invulnerable = false;
};
