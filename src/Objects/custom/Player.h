#pragma once
#include "../Actor.h"
#include "./Turret.h"
#include "Bullet.h"

enum class Powerup : int {
	LASER = 0,
	CANNONS = 1,
	TURRETS = 2,
	COUNT = 3
};

class Player : public Actor {
private:
	int lives = PLAYER_LIVES;
	float speed = BASE_PLAYER_SPEED;

	Turret* turretLeft = nullptr;
	Turret* turretRight = nullptr;

public:
	Player(std::string _path = PLAYER_SPRITE_PATH) :
		Actor(_path, Vector2(0.f, 0.f), Vector2(32, 32)) {
		health = PLAYER_HEALTH;
		maxHealth = PLAYER_HEALTH;

		transform->position = Vector2(0.f, 0.f);
		transform->scale = Vector2(2.f, 2.f);

		rbComp->AddCollider(new AABB(transform->position, transform->GetSize()));
		rbComp->SetAngularDrag(0.5f);
		rbComp->SetLinearDrag(0.5f);

		RefreshShooting();
	}
	Player(Player&) = delete;
	Player& operator=(const Player&) = delete;

	virtual void Update() override;

	void HandleMovement();
	void HandleShooting(float dt);
	void Shoot();
	void OnCollision(Collidable* other) override;
	void TakeDamage(int amount) override;
	void ResetForStage() {
		turretLeft = nullptr;
		turretRight = nullptr;
		for(int i = 0; i < (int)Powerup::COUNT; ++i) powerUpFlags[i] = false;
		speed = BASE_PLAYER_SPEED;
		shootTimer = 0.0f;
		cannonEnergy = MAX_CANNON_ENERGY;
		laserEnergy = MAX_LASER_ENERGY;
		shields = maxShields;
		invulnerable = false;
		lastX = transform->position.x;
		rbComp->SetVelocity({ 0.f, 0.f });
	}
	void RefreshShooting() {
		TimeManager::GetInstance()->SubscribeEvent(1.0f / BULLETS_PER_SECOND, [this]() { RefreshShooting(); });
	}

	void OnSceneEnter() {
		ResetForStage();
		RefreshShooting();
	}
	virtual bool IsPersistent() const override { return true; }

	std::function<void(int current, int max)> OnLivesChanged;

	int GetLives() { return lives; }
	void SetLives(int _lives) {
		lives = _lives;
		OnLivesChangedEvent();
	}
	void IncrementLives(int amount) {
		lives += amount;
		OnLivesChangedEvent();
	}
	void DecrementLives(int amount) {
		lives -= amount;
		OnLivesChangedEvent();
	}
	void OnLivesChangedEvent() {
		if(OnLivesChanged) 	OnLivesChanged(health, maxHealth);
	}

	float GetSpeed() { return speed; }
	void SetSpeed(float _speed) { speed = _speed; }
	void ScaleSpeed(float scale) { speed *= scale; }

	static Player* GetInstance() {
		static Player instance;
		return &instance;
	}

	bool GetPowerupFlag(Powerup powerup) { return powerUpFlags[(int)powerup]; }
	void SetPowerupFlag(Powerup powerup, bool state) { powerUpFlags[(int)powerup] = state; }
	void ActivateTurrets();

	void RefillCannon() { cannonEnergy = MAX_CANNON_ENERGY; }
	void RefillLaser() { laserEnergy = MAX_LASER_ENERGY; }
	void RefillShields() { shields = maxShields; }
	int GetShields() const { return shields; }

protected:
	void OnDeath() override;

private:
	void ClampToScreen();

	bool powerUpFlags[(int)Powerup::COUNT] = {};
	int maxShields = PLAYER_SHIELDS;
	int shields = PLAYER_SHIELDS;
	bool invulnerable = false;
	bool pendingImpactSfx = false;
	float lastX = 0.0f;

	float shootCooldown = 0.2f; // 5 shots/sec
	float shootTimer = 0.0f;

	int cannonEnergy = MAX_CANNON_ENERGY;
	int laserEnergy = MAX_LASER_ENERGY;
};
