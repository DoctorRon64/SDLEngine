#pragma once
#include <memory>
#include "../custom/Enemy.h"
#include "states/LinearMoveState.h"
#include "states/CircleMoveState.h"
#include "states/AmoebaSplitState.h"

class AmoebaEnemy : public Enemy {
public:
	AmoebaEnemy(Vector2 spawn)
		: Enemy(ENEMY_AMOEBA_SPRITE_PATH, spawn, { 32, 32 }),
		splitRemaining(std::make_shared<int>(0)) {
		float h = (float)RenderManager::GetInstance()->WINDOW_HEIGHT;
		float w = (float)RenderManager::GetInstance()->WINDOW_WIDTH;

		Vector2 start = { -transform->GetSize().x, Randomness::Range(0.f, h) };
		splitCenter = { w * 0.6f, h / 2.f };
		transform->position = start;

		stateManager.AddState(new LinearMoveState(&transform->position, start, splitCenter, 90.f));
		stateManager.AddState(new AmoebaSplitState(&transform->position, this));
		stateManager.AddState(new LinearMoveState(&transform->position, splitCenter, { -transform->GetSize().x, splitCenter.y }, 90.f));
		InitHp(25);
	}

	AmoebaEnemy(Vector2 center, std::shared_ptr<int> remaining, float startAngle)
		: Enemy(ENEMY_AMOEBA_SPRITE_PATH, center, { 32, 32 }),
		isClone(true),
		splitRemaining(remaining),
		splitCenter(center) {
		float rad = startAngle * 3.14159265f / 180.0f;
		transform->position = { center.x + cos(rad) * splitRadius, center.y + sin(rad) * splitRadius };

		stateManager.AddState(new CircleMoveState(&transform->position, center, splitRadius, 180.f, 2, startAngle));
		InitHp(15);
	}

	void Update() override {
		Enemy::Update();

		if(!isClone) return;

		if(stateManager.IsFinished() && !IsPendingDestroy()) {
			MarkCloneComplete();
			WaveManager::GetInstance()->UnregisterEnemy();
			Destroy();
			return;
		}

		if(IsPendingDestroy()) {
			MarkCloneComplete();
		}
	}

	void SpawnSplitClones() {
		if(splitSpawned) return;
		splitSpawned = true;

		const int cloneCount = 8;
		*splitRemaining = cloneCount;
		float angleStep = 360.f / (float)cloneCount;

		for(int i = 0; i < cloneCount; ++i) {
			float angle = i * angleStep;
			SpawnManager::Instance().SpawnObject(new AmoebaEnemy(splitCenter, splitRemaining, angle));
		}
	}

	bool AreSplitClonesDone() const {
		return splitSpawned && splitRemaining && *splitRemaining <= 0;
	}

protected:
	void OnDeath() override {
		if(isClone) {
			MarkCloneComplete();
		}
		Enemy::OnDeath();
	}

private:
	void MarkCloneComplete() {
		if(!isClone || cloneCounted) return;
		cloneCounted = true;
		if(splitRemaining && *splitRemaining > 0) {
			(*splitRemaining)--;
		}
	}

	bool isClone = false;
	bool splitSpawned = false;
	bool cloneCounted = false;
	float splitRadius = 60.f;
	Vector2 splitCenter = { 0.f, 0.f };
	std::shared_ptr<int> splitRemaining;
};
