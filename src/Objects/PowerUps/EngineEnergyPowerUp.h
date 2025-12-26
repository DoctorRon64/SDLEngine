#pragma once
#include "PowerUp.h"
#include "../custom/Player.h"
class EngineEnergyPowerUp :
    public PowerUp
{
    void OnCollect() override {
        Player::GetInstance()->ScaleSpeed(ENGINE_POWERUP_SCALE_VALUE);
    }
};

