#pragma once
#include "PowerUp.h"
#include "../custom/Player.h"
class ShieldEnergyPowerUp :
    public PowerUp
{
public:
    ShieldEnergyPowerUp();
    void OnCollect() override {
        Player::GetInstance()->RefillShields();
    }
};

