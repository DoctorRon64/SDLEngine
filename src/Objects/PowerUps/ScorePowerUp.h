#pragma once
#include "PowerUp.h"
class ScorePowerUp :
    public PowerUp
{
public:
    ScorePowerUp();
    void OnCollect() override {
        ScoreManager::GetInstance()->AddScore(SCORE_POWERUP_VALUE);
    }
};

