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
	if(InputManager::GetInstance()->GetEvent(SDLK_W, HOLD)) move.y -= 1.0f;
	if(InputManager::GetInstance()->GetEvent(SDLK_S, HOLD)) move.y += 1.0f;
	if(InputManager::GetInstance()->GetEvent(SDLK_A, HOLD)) move.x -= 1.0f;
	if(InputManager::GetInstance()->GetEvent(SDLK_D, HOLD)) move.x += 1.0f;

	// Arrow keys
	if(InputManager::GetInstance()->GetArrowInput(SDLK_UP)) move.y -= 1.0f;
	if(InputManager::GetInstance()->GetArrowInput(SDLK_DOWN)) move.y += 1.0f;
	if(InputManager::GetInstance()->GetArrowInput(SDLK_LEFT)) move.x -= 1.0f;
	if(InputManager::GetInstance()->GetArrowInput(SDLK_RIGHT)) move.x += 1.0f;

	// Gamepad
	move.x += InputManager::GetInstance()->GetGamepadAxisX();
	move.y += InputManager::GetInstance()->GetGamepadAxisY();

	if(move.LengthSquared() > 1.0f) {
		move.Normalize();
	}

	const float baseSpeed = 260.0f;
	rbComp->SetVelocity(move * (baseSpeed * speed));
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
		pendingImpactSfx = true;
		TakeDamage(PLAYER_HEALTH + PLAYER_SHIELDS);
		pendingImpactSfx = false;
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
	const std::string& sfx = pendingImpactSfx ? SFX_PLAYER_IMPACT_PATH : SFX_HURT_PLAYER_PATH;
	AudioManager::GetInstance()->PlaySound(sfx);
}

void Player::Shoot() {
	// Main gun
	Vector2 mainGunPos = Vector2(transform->position.x + transform->GetSize().x, transform->position.y + transform->GetSize().y / 2);
	Bullet* mainBullet = new Bullet(true, BULLET_SPRITE_PATH, mainGunPos);
	mainBullet->SetLayer(20);
	SpawnManager::Instance().SpawnObject(mainBullet);

	// LASER power-up bullets
	if(powerUpFlags[(int)Powerup::LASER]) {
		Vector2 laserPos = Vector2(transform->position.x + transform->GetSize().x / 2, transform->position.y + transform->GetSize().y);
		Bullet* laserBullet = new Bullet(true, BULLET_SPRITE_PATH, laserPos);
		laserBullet->SetLayer(20);
		SpawnManager::Instance().SpawnObject(laserBullet);
	}

	// CANNONS power-up bullets
	if(powerUpFlags[(int)Powerup::CANNONS]) {
		Vector2 cannonPos1 = Vector2(transform->position.x + transform->GetSize().x, transform->position.y + transform->GetSize().y);
		Vector2 cannonPos2 = Vector2(transform->position.x, transform->position.y + transform->GetSize().y);
		Bullet* cannonBullet1 = new Bullet(true, BULLET_SPRITE_PATH, cannonPos1);
		cannonBullet1->SetLayer(20);
		SpawnManager::Instance().SpawnObject(cannonBullet1);

		Bullet* cannonBullet2 = new Bullet(true, BULLET_SPRITE_PATH, cannonPos2);
		cannonBullet2->SetLayer(20);
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
	auto* rm = RenderManager::GetInstance();
	Vector2 size = transform->GetSize();

	float minX = 0.0f;
	float minY = 0.0f;
	float maxX = rm->WINDOW_WIDTH - size.x;
	float maxY = rm->WINDOW_HEIGHT - size.y;

	Vector2 pos = transform->position;
	Vector2 vel = rbComp->GetVelocity();

	if(pos.x < minX) {
		pos.x = minX;
		vel.x = 0.0f;
	}
	else if(pos.x > maxX) {
		pos.x = maxX;
		vel.x = 0.0f;
	}

	if(pos.y < minY) {
		pos.y = minY;
		vel.y = 0.0f;
	}
	else if(pos.y > maxY) {
		pos.y = maxY;
		vel.y = 0.0f;
	}

	transform->position = pos;
	rbComp->SetVelocity(vel);
}

void Player::OnDeath() {
	if(OnDeathEvent) {
		OnDeathEvent();
	}
}
