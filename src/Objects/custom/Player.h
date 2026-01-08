#pragma once
#include "../Actor.h"
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

public:
	Player(std::string _path = "res/player_sprite.png") :
		Actor(_path, Vector2(0.f, 0.f), Vector2(32, 32)) {
		health = PLAYER_HEALTH;
		maxHealth = PLAYER_HEALTH;

		transform->position = Vector2(0.f, 0.f);
		transform->scale = Vector2(2.f, 2.f);

		rbComp->SetAngularDrag(0.5f);
		rbComp->SetLinearDrag(0.5f);

		RefreshShooting();
	}
	Player(Player&) = delete;
	Player& operator=(const Player&) = delete;

	virtual void Update() override;
	void HandleMovement();
	void HandleShooting();
	void Shoot();
	void RefreshShooting() {
		canShoot = true;
		TimeManager::GetInstance()->SubscribeEvent(1.0f / BULLETS_PER_SECOND, [this]() { RefreshShooting(); });
	}

	virtual bool IsPersistent() const override { return true; }

	std::function<void(int current, int max)> OnLivesChanged;

	int GetLives() { return lives; }
	void SetLives(int _lives) { lives = _lives; }
	void IncrementLives(int amount) { lives += amount; }
	void DecrementLives(int amount) { lives -= amount; }

	float GetSpeed() { return speed; }
	void SetSpeed(float _speed) { speed = _speed; }
	void ScaleSpeed(float scale) { speed *= scale; }

	static Player* GetInstance() {
		static Player instance;
		return &instance;
	}

	bool GetPowerupFlag(Powerup powerup) { return powerUpFlags[(int)powerup]; }
	void SetPowerupFlag(Powerup powerup, bool state) { powerUpFlags[(int)powerup] = state; }

private:
	void ClampToScreen();

	bool canShoot;
	bool powerUpFlags[(int)Powerup::COUNT] = {};
	int shields = 100;
	bool invulnerable = false;
};
