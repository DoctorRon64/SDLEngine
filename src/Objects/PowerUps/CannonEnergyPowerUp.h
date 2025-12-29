#pragma once
#include "PowerUp.h"
#include "../custom/Player.h"
class CannonEnergyPowerUp :
    public PowerUp
{
public:
    void OnCollect() override {
        Player::GetInstance()->SetPowerupFlag(Powerup::CANNONS, true);
    }
};

