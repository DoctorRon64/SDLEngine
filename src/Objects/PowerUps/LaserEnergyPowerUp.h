#pragma once
#include "PowerUp.h"
#include "../custom/Player.h"
class LaserEnergyPowerUp :
    public PowerUp
{
    void OnCollect() override {
        Player::GetInstance()->SetPowerupFlag(Powerup::LASER, true);
    }
};

