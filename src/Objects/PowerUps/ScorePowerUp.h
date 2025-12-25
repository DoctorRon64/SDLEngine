#pragma once
#include "PowerUp.h"
class ScorePowerUp :
    public PowerUp
{
    void OnCollect() override {
        ScoreManager::GetInstance()->AddScore(SCORE_POWERUP_VALUE);
    }
};

