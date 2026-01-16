#pragma once
#include "../../components/Collidable.h"
#include "../custom/Player.h"
#include "../Image.h"
#include "../Object.h"

class PowerUp : public Image, public Collidable {
protected:
	int charge = 0;
	int maxCharge = 5;

	PowerUp(
		std::string _name = POWERUP_SPRITE_PATH,
		Vector2 _pos = Vector2(0.f, 0.f),
		Vector2 _size = Vector2(32.f, 32.f)
	) : Image(_name, _pos, _size), Collidable(rbComp) {
		rbComp->AddCollider(new AABB(_pos, _size));
		transform->scale = { 2.f, 2.f };
	}

	virtual void OnCollect() = 0;

	void OnCollision(Collidable* other) override {
		if(auto player = dynamic_cast<Player*>(other)) {
			OnCollect();
			Destroy();
		}

		if(auto* b = dynamic_cast<Bullet*>(other)) {
			if(b->IsPlayerBullet()) {
				charge = std::min(charge + 1, maxCharge);
				b->Destroy();
			}
		}
		if(auto* p = dynamic_cast<Player*>(other)) {
			OnCollect();
			Destroy();
		}
	}
};
