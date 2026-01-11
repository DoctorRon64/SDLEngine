#pragma once
#include "../custom/Enemy.h"

class BubbleEnemy : public Enemy {
private:
	float angle = 0.f;
	Vector2 circleCenter;

public:
	BubbleEnemy(Vector2 spawn)
		: Enemy("res/enemies/bubble_sprite.png", spawn, { 32, 32 }) {
		state = EnemyState::SIMPLE_MOVE;
		velocity = { -speed, 0 };
		InitHp(2);
	}

protected:

	//virtual void Update() override {
	//	if(!reachedThird) {
	//		if(transform->position.x <= WINDOW_WIDTH * 0.66f) {
	//			reachedThird = true;
	//			startAngle = currentAngle;
	//		}
	//		transform->position.x -= speed * dt;
	//	}
	//	else if(angleTravelled < 300.f) {
	//		angleTravelled += angularSpeed * dt;
	//		transform->position = center + CircleOffset(angleTravelled);
	//	}
	//	else {
	//		transform->position += straightDir * speed * dt;
	//	}
	//}

	void UpdateState(float dt) override {
		switch(state) {
			case EnemyState::SIMPLE_MOVE: MoveStraight(dt); break;
			case EnemyState::CIRCLE_MOVE: MoveCircle(dt); break;
			case EnemyState::CHASE: MoveStraight(dt); break;
		}
	}

	void MoveStraight(float dt) {
		transform->position += velocity * dt;

		if(transform->position.x < RenderManager::GetInstance()->WINDOW_WIDTH * 0.66f) {
			state = EnemyState::CIRCLE_MOVE;
			circleCenter = transform->position;
			angle = 0.f;
		}
	}

	void MoveCircle(float dt) {
		const float DEG2RAD = 3.14159265f / 180.0f;
		float radius = 100.f;
		angle += 180.f * dt;

		float rad = angle * DEG2RAD;
		transform->position.x = circleCenter.x + cos(rad) * radius;
		transform->position.y = circleCenter.y + sin(rad) * radius;

		if(angle >= 300.f) {
			state = EnemyState::CHASE;
			velocity = { -speed * 1.5f, 0 };
		}
	}
};
