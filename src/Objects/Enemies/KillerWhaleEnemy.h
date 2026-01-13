#pragma once
#include "../custom/Enemy.h"
#include "states/WaveMoveState.h"

class KillerWhaleEnemy : public Enemy {
private:
	float waveTime = 0.f;

public:
	KillerWhaleEnemy(Vector2 spawn)
		: Enemy(ENEMY_WHALE_SPRITE_PATH, spawn, { 32,32 }) {
		stateManager.SetState(new WaveMoveState(transform));
		InitHp(3);
	}

protected:
	void UpdateState(float dt) override {
		waveTime += dt;

		transform->position.x += velocity.x * dt;
		transform->position.y += sin(waveTime * 5.f) * 50.f * dt; // amplitude 50, speed factor 5
	}
};
