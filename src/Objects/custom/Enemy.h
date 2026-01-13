#pragma once
#include "../Actor.h"

enum class EnemyState {
	STAY,
	SIMPLE_MOVE,
	CIRCLE_MOVE,
	CHASE
};

class Enemy : public Actor {
protected:
	EnemyState state = EnemyState::STAY;
	float stateTimer = 0.f;

	int scoreValue = 100;
	float speed = 50.f;

	Vector2 velocity = { 0, 0 };

	virtual void OnDeath() override;

public:
	Enemy(
		const std::string& texture,
		Vector2 spawnPos,
		Vector2 size
	);
	virtual void Update() override;

protected:
	EnemyStateManager stateManager;

	float shootCooldown = 1.f;
	float shootTimer = 0.f;

	void UpdateShooting(float dt);

	virtual void Shoot() {}
	virtual void UpdateState(float dt) = 0;

	void ClampToScreen() {
		auto* rm = RenderManager::GetInstance();
		Vector2 size = transform->GetSize();

		transform->position.x = std::clamp(
			transform->position.x,
			0.0f,
			rm->WINDOW_WIDTH - size.x
		);

		transform->position.y = std::clamp(
			transform->position.y,
			0.0f,
			rm->WINDOW_HEIGHT - size.y
		);
	}
};