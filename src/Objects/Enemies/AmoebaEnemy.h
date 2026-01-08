#pragma once
#include "../custom/Enemy.h"

class AmoebaEnemy : public Enemy {
public:
	enum State { MOVE_IN, SPLIT, ORBIT, RECOMBINE };
	State state = MOVE_IN;
	float angle = 0.f;
	int orbits = 0;

	AmoebaEnemy(Vector2 spawn)
		: Enemy("res/enemies/amoeba_sprite.png", spawn, { 32,32 }) {
		velocity = { -speed, 0 };
		hp = 1;
	}

	void UpdateState(float dt) override {
		const float PI = 3.14f;
		Vector2 center = GetTransform()->position / 2;

		switch(state) {
			case MOVE_IN:
			MoveTowards(transform, { static_cast<float>(RenderManager::GetInstance()->WINDOW_WIDTH / 2), static_cast<float>(RenderManager::GetInstance()->WINDOW_HEIGHT / 2) }, speed, dt);
			if(stateTimer > 1.5f) state = SPLIT;
			break;

			case ORBIT:
			Orbit(transform, center, 80.f, angle, 3.f, dt);
			if(angle > 2 * PI * 2) state = RECOMBINE;
			break;
		}
	}
};