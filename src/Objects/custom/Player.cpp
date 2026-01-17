#include "pch.h"
#include "Player.h"
#include "Enemy.h"
#include "Turret.h"

void Player::Update() {
	float dt = TimeManager::GetInstance()->GetDeltaTime();

	HandleMovement();
	HandleShooting(dt);

	float previousX = lastX;
	Image::Update();
	float deltaX = transform->position.x - previousX;
	lastX = transform->position.x;

	if(turretLeft) turretLeft->GetTransform()->position = transform->position + Vector2(-TURRET_OFFSET_X, 0);
	if(turretRight) turretRight->GetTransform()->position = transform->position + Vector2(TURRET_OFFSET_X, 0);

	if(turretLeft) turretLeft->ApplyPlayerMovement(deltaX);
	if(turretRight) turretRight->ApplyPlayerMovement(deltaX);

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
		AudioManager::GetInstance()->PlaySound(SFX_LASER_SHOOT_PATH);
		shootTimer = shootCooldown;
	}
}

void Player::ActivateTurrets() {
	if(!turretLeft && !turretRight) {
		turretLeft = new Turret(transform->position + Vector2(-TURRET_OFFSET_X, 0));
		turretRight = new Turret(transform->position + Vector2(TURRET_OFFSET_X, 0));
		SpawnManager::Instance().SpawnObject(turretLeft);
		SpawnManager::Instance().SpawnObject(turretRight);
	}
}

void Player::OnCollision(Collidable* other) {
	if(dynamic_cast<Enemy*>(other)) {
		TakeDamage(PLAYER_HEALTH + PLAYER_SHIELDS);
	}
}

void Player::TakeDamage(int amount) {
	if(amount <= 0 || invulnerable) return;

	int remainingDamage = amount;
	if(shields > 0) {
		int absorbed = std::min(shields, remainingDamage);
		shields -= absorbed;
		remainingDamage -= absorbed;
	}

	if(remainingDamage > 0) {
		Actor::TakeDamage(remainingDamage);
	}

	invulnerable = true;
	TimeManager::GetInstance()->SubscribeEvent(
		PLAYER_INVULNERABILITY_SECONDS,
		[this]() { invulnerable = false; }
	);
	AudioManager::GetInstance()->PlaySound(SFX_HURT_PLAYER_PATH);
}

void Player::Shoot() {
	// Main gun
	Vector2 mainGunPos = Vector2(transform->position.x + transform->GetSize().x, transform->position.y + transform->GetSize().y / 2);
	Bullet* mainBullet = new Bullet(true);
	mainBullet->SetLayer(20);
	mainBullet->GetTransform()->position = mainGunPos;
	SpawnManager::Instance().SpawnObject(mainBullet);

	// LASER power-up bullets
	if(powerUpFlags[(int)Powerup::LASER]) {
		Vector2 laserPos = Vector2(transform->position.x + transform->GetSize().x / 2, transform->position.y + transform->GetSize().y);
		Bullet* laserBullet = new Bullet();
		laserBullet->SetLayer(20);
		laserBullet->GetTransform()->position = laserPos;
		SpawnManager::Instance().SpawnObject(laserBullet);
	}

	// CANNONS power-up bullets
	if(powerUpFlags[(int)Powerup::CANNONS]) {
		Vector2 cannonPos1 = Vector2(transform->position.x + transform->GetSize().x, transform->position.y + transform->GetSize().y);
		Vector2 cannonPos2 = Vector2(transform->position.x, transform->position.y + transform->GetSize().y);
		Bullet* cannonBullet1 = new Bullet();
		cannonBullet1->SetLayer(20);
		cannonBullet1->GetTransform()->position = cannonPos1;
		SpawnManager::Instance().SpawnObject(cannonBullet1);

		Bullet* cannonBullet2 = new Bullet();
		cannonBullet2->SetLayer(20);
		cannonBullet2->GetTransform()->position = cannonPos2;
		SpawnManager::Instance().SpawnObject(cannonBullet2);
	}

	// TURRETS shooting
	if(powerUpFlags[(int)Powerup::TURRETS]) {
		if(turretLeft) turretLeft->Shoot();
		if(turretRight) turretRight->Shoot();
	}

	// Play sound once per shoot
	AudioManager::GetInstance()->PlaySound(SFX_LASER_SHOOT_PATH);
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

void Player::OnDeath() {
	if(OnDeathEvent) {
		OnDeathEvent();
	}
}
