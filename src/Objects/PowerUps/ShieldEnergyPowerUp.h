#pragma once
#include "PowerUp.h"
class ShieldEnergyPowerUp :
    public PowerUp
{
    void OnCollect() override {
        Player::GetInstance()->HealToMax();
    }
};

