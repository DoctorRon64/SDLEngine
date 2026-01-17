#pragma once
#include "../custom/Player.h"
#include "PowerUp.h"
class TwinTurretsPowerUp :
	public PowerUp {
public:
	TwinTurretsPowerUp();
	void OnCollect() override {
		Player::GetInstance()->SetPowerupFlag(Powerup::TURRETS, true);
		Player::GetInstance()->ActivateTurrets();
	}
};
