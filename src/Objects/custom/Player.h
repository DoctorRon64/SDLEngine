#pragma once
#include "../Image.h"
#include "./baseEnemy.h"
#include "./bullet.h"

class Player : public Image {
public:
	Player(std::string _name = "res/man.png") : Image(_name, Vector2(0.f, 0.f), Vector2(992.f, 1542.f)) {
		Vector2 middle = Vector2((float)renderManager->WINDOW_WIDTH / 2, (float)renderManager->WINDOW_HEIGHT / 2);
		transform->position = middle;
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
		// Ensure texture is loaded into renderer/cache
		renderManager->LoadTexture(tex);

		// Allocate bullet at player's position
		auto b = new bullet(tex, transform->position);
		if(!b) {
			std::cout << "Shoot(): allocation failed\n";
			return;
		}

		// Place bullet slightly above the player so it is clearly visible (tweak offset as needed)
		b->GetTransform()->position = transform->position;
		b->GetTransform()->position.y -= 20.0f;

		// Ensure visible size & render order
		b->GetTransform()->scale = Vector2(10.0f, 10.0f);
		b->SetLayer(20); // render above default objects (adjust as your engine expects)

		// Give a noticeable initial velocity (increase magnitude if your physics are small-scale)
		if(b->GetRigidBody()) {
			// Use a larger velocity so the bullet is visibly moving on screen
			b->GetRigidBody()->SetVelocity(Vector2(0.0f, -600.0f));
			// Alternatively: b->GetRigidBody()->AddForce(Vector2(0.0f, -2000.0f));
		}

		// Spawn the object through the spawner and validate the result
		spawnerManager.SpawnObject(b);
		auto c = spawnerManager.GetSpawnedObject();

		std::cout << "Shoot(): created ptr=" << b
			<< " spawnedReturned=" << c
			<< " pos=(" << b->GetTransform()->position.x << "," << b->GetTransform()->position.y << ")"
			<< " scale=(" << b->GetTransform()->scale.x << "," << b->GetTransform()->scale.y << ")"
			<< " size=(" << b->GetTransform()->size.x << "," << b->GetTransform()->size.y << ")"
			<< std::endl;

		// If spawner failed to register the object, avoid leaking memory
		if(c == nullptr) {
			std::cout << "Shoot(): spawner returned null — deleting bullet to avoid leak\n";
			delete b;
		}
	}
};
