#pragma once

#include "../../components/Collidable.h"
#include "Enemy.h"
#include "Player.h"

class Bullet : public Image, public Collidable {
public:
	Bullet(
		bool _isPlayer = true,
		std::string _name = BULLET_SPRITE_PATH,
		Vector2 _pos = Vector2(0.f, 0.f),
		Vector2 _size = Vector2(32.f, 32.f)
	);

	~Bullet() override = default;
	void Update() override;

	virtual void OnCollision(Collidable* other) override;
	Object* GetOwner() { return this; }

	const bool IsPlayerBullet() { return isPlayerBullet; }

private:
	bool isPlayerBullet = true;
	float bulletSpeed = 350.f;
};
