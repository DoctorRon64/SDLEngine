#include "pch.h"
#include "Player.h"

void Player::Update() {
	float dt = TimeManager::GetInstance()->GetDeltaTime();

	HandleMovement();
	HandleShooting(dt);

	Image::Update();

	ClampToScreen();
}

void Player::HandleMovement() {
	Vector2 move(0.f, 0.f);

	// Keyboard WASD
	if(InputManager::GetInstance()->GetEvent(SDLK_W, HOLD)) move.y -= speed;
	if(InputManager::GetInstance()->GetEvent(SDLK_S, HOLD)) move.y += speed;
	if(InputManager::GetInstance()->GetEvent(SDLK_A, HOLD)) move.x -= speed;
	if(InputManager::GetInstance()->GetEvent(SDLK_D, HOLD)) move.x += speed;

	// Arrow keys
	if(InputManager::GetInstance()->GetArrowInput(SDLK_UP)) move.y -= speed;
	if(InputManager::GetInstance()->GetArrowInput(SDLK_DOWN)) move.y += speed;
	if(InputManager::GetInstance()->GetArrowInput(SDLK_LEFT)) move.x -= speed;
	if(InputManager::GetInstance()->GetArrowInput(SDLK_RIGHT)) move.x += speed;

	// Gamepad
	move.x += InputManager::GetInstance()->GetGamepadAxisX();
	move.y += InputManager::GetInstance()->GetGamepadAxisY();

	rbComp->AddForce(move * 300.f);
}

void Player::HandleShooting(float dt) {
	bool fireHeld =
		InputManager::GetInstance()->GetEvent(SDLK_SPACE, HOLD) ||
		InputManager::GetInstance()->GetLeftClick() ||
		InputManager::GetInstance()->GetGamepadButton(SDL_GAMEPAD_BUTTON_SOUTH) ||
		InputManager::GetInstance()->GetArrowInput(UP);

	if(!fireHeld) {
		shootTimer = 0.0f; // instant response on re-press
		return;
	}

	shootTimer -= dt;

	if(shootTimer <= 0.0f) {
		Shoot();
		AudioManager::GetInstance()->PlaySound("res/audio/sfx/laserShoot.wav");
		shootTimer = shootCooldown;
	}
}

void Player::Shoot() {
	auto* bullet = new Bullet(true);
	bullet->SetLayer(20);
	Vector2 pos = Vector2(transform->position.x + transform->GetSize().x, transform->position.y + transform->GetSize().y / 2);
	bullet->GetTransform()->position = pos;

	SpawnManager::Instance().SpawnObject(bullet);

	if(powerUpFlags[(int)Powerup::LASER]) {
		Bullet* laserBullet = new Bullet();
		laserBullet->SetLayer(20);
		Vector2 pos1 = Vector2(transform->position.x + transform->GetSize().x / 2, transform->position.y + transform->GetSize().y);
		laserBullet->GetTransform()->position = pos1;
		SpawnManager::Instance().SpawnObject(laserBullet);
		AudioManager::GetInstance()->PlaySound("res/audio/sfx/laserShoot.wav");
	}
	else if(powerUpFlags[(int)Powerup::CANNONS]) {
		Bullet* cannonsBullet1 = new Bullet();
		cannonsBullet1->SetLayer(20);
		Vector2 pos1 = Vector2(transform->position.x + transform->GetSize().x, transform->position.y + transform->GetSize().y);
		cannonsBullet1->GetTransform()->position = pos1;
		SpawnManager::Instance().SpawnObject(cannonsBullet1);
		AudioManager::GetInstance()->PlaySound("res/audio/sfx/laserShoot.wav");

		Bullet* cannonsBullet2 = new Bullet();
		cannonsBullet2->SetLayer(20);
		Vector2 pos2 = Vector2(transform->position.x, transform->position.y + transform->GetSize().y);
		cannonsBullet2->GetTransform()->position = pos2;
		SpawnManager::Instance().SpawnObject(cannonsBullet2);
		AudioManager::GetInstance()->PlaySound("res/audio/sfx/laserShoot.wav");
	}
}

void Player::ClampToScreen() {
	{
		if(transform->position.x <= 0 || transform->position.x >= RenderManager::GetInstance()->WINDOW_WIDTH - transform->GetSize().x) {
			rbComp->SetVelocity({ 0, rbComp->GetVelocity().y });
		}

		if(transform->position.y <= 0 || transform->position.y >= RenderManager::GetInstance()->WINDOW_HEIGHT - transform->GetSize().y) {
			rbComp->SetVelocity({ rbComp->GetVelocity().x, 0 });
		}
	}
}