#pragma once
#include "../Actor.h"
#include "Bullet.h"

class Player : public Actor {
private:
	int lives = PLAYER_LIVES;
	float speed = BASE_PLAYER_SPEED;

public:
	Player(std::string _path = "res/man.png") :
		Actor(_path, Vector2(0.f, 0.f), Vector2(992, 1542), PLAYER_HEALTH, PLAYER_HEALTH) {
		transform->position = Vector2(0.f, 0.f);
		transform->scale = Vector2(.1f, .1f);

		rbComp->SetAngularDrag(0.5f);
		rbComp->SetLinearDrag(0.5f);
	}
	Player(Player&) = delete;
	Player& operator=(const Player&) = delete;

	virtual void Update() override;
	void HandleMovement();
	void HandleShooting();
	void Shoot();

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

private:
	void ClampToScreen();

	float shootCooldown = 0.2f;
	float shootTimer = 0.0f;
	int shields = 100;
	bool invulnerable = false;
};
