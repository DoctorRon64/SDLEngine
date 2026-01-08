#pragma once

#include "../../components/Collidable.h"
#include "Enemy.h"
#include "Player.h"

class Bullet : public Image, public Collidable {
public:
	Bullet(
		bool _isPlayer = true,
		std::string _name = "res/bullet.png",
		Vector2 _pos = Vector2(0.f, 0.f),
		Vector2 _size = Vector2(400.f, 400.f)
	);

	~Bullet() override = default;
	void Update() override;

protected:
	void OnCollision(Object* other) override;

private:
	bool isPlayerBullet = true;
	float bulletSpeed = 350.f;
};
