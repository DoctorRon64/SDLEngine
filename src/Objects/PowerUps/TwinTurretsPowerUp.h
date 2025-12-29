#pragma once
#include "PowerUp.h"
#include "../custom/Player.h"
class TwinTurretsPowerUp :
    public PowerUp
{
    void OnCollect() override {
        Player::GetInstance()->SetPowerupFlag(Powerup::TURRETS, true);
    }
};

