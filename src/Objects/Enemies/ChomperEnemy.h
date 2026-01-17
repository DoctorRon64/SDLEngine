#pragma once
#include "../custom/Enemy.h"
#include "states/CircleDriftState.h"

class ChomperEnemy : public Enemy {
public:
	ChomperEnemy(Vector2 spawn) : Enemy(ENEMY_CHOMPER_SPRITE_PATH, spawn, { 32, 32 }) {
		float radius = 60.f;
		Vector2 center = spawn + Vector2(-radius, 0.f);
		stateManager.AddState(new CircleDriftState(&transform->position, center, radius, 120.f, 20.f));
		InitHp(15);
	}

	static void SpawnLine(float x) {
		float h = (float)RenderManager::GetInstance()->WINDOW_HEIGHT;
		float spacing = 64.f;
		int count = static_cast<int>(std::ceil(h / spacing));

		for(int i = 0; i <= count; ++i) {
			Vector2 pos = { x, i * spacing };
			SpawnManager::Instance().SpawnObject(new ChomperEnemy(pos));
		}
	}
};
