#pragma once
#include "PowerUp.h"
#include "../custom/Player.h"
class ShieldEnergyPowerUp :
    public PowerUp
{
    void OnCollect() override {
        Player::GetInstance()->HealToMax();
    }
};

