#pragma once
#include "../custom/Player.h"
#include "PowerUp.h"
class CannonEnergyPowerUp :
	public PowerUp {
public:
	void OnCollect() override {
		Player::GetInstance()->SetPowerupFlag(Powerup::CANNONS, true);
		Player::GetInstance()->RefillCannon();
	}
};
