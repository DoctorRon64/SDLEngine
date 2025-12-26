#include "pch.h"
#include "Player.h"

void Player::Update() {
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	shootTimer -= dt;

	HandleMovement();
	HandleShooting();
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

void Player::HandleShooting() {
	{
		float dt = TimeManager::GetInstance()->GetDeltaTime();
		shootTimer -= dt;

		bool fireInput = InputManager::GetInstance()->GetEvent(SDLK_SPACE, DOWN) ||
			InputManager::GetInstance()->GetLeftClick() ||
			InputManager::GetInstance()->GetGamepadButton(SDL_GAMEPAD_BUTTON_SOUTH) ||
			InputManager::GetInstance()->GetArrowInput(UP);

		if(fireInput && shootTimer <= 0.0f) {
			Shoot();
			shootTimer = 0.2f;
		}
	}
}

void Player::Shoot() {
	const std::string tex = "res/bullet.png";
	auto b = new Bullet();

	b->SetLayer(20);

	Vector2 pos = Vector2(transform->position.x, transform->position.y);

	b->GetTransform()->position = pos;

	SpawnManager::Instance().SpawnObject(b);
	AudioManager::GetInstance()->PlaySound("res/audio/sfx/laserShoot.wav");
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