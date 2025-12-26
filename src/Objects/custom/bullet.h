#pragma once
#include "Enemy.h"
#include "Player.h"

class Bullet : public Image {
public:
	bool isPlayerBullet = true;

	Bullet(std::string _name = "res/bullet.png", Vector2 _pos = Vector2(0.f, 0.f), Vector2 _size = Vector2(40.f, 40.f), bool _isPlayer = true);
	~Bullet();

	void Update() override;

private:
	void CheckCollision();

	float bulletSpeed = 350.f;
};