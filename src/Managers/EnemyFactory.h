#pragma once
#include "../Objects/custom/Enemy.h"
#include "../Objects/Enemies/AmoebaEnemy.h"
#include "../Objects/Enemies/BeholderEnemy.h"
#include "../Objects/Enemies/BubbleEnemy.h"
#include "../Objects/Enemies/ChomperEnemy.h"
#include "../Objects/Enemies/CirclerEnemy.h"
#include "../Objects/Enemies/KillerWhaleEnemy.h"
#include "../Objects/Enemies/MedusaEnemy.h"
#include "../Objects/Enemies/VerticleMedusaEnemy.h"
class EnemyFactory {
	using SpawnFunction = std::function<void()>;
private:
	EnemyFactory() = default;
	~EnemyFactory() = default;
	EnemyFactory(const EnemyFactory&) = delete;
	EnemyFactory& operator=(const EnemyFactory&) = delete;

	Vector2 GetRandomSpawnPos() {
		return {
			Randomness::Range(RenderManager::GetInstance()->WINDOW_WIDTH / 2.f, RenderManager::GetInstance()->WINDOW_WIDTH),
			Randomness::Range(0.f, RenderManager::GetInstance()->WINDOW_HEIGHT)
		};
	};

public:
	const SpawnFunction spawnFunctions[ENEMY_ID_COUNT] = {
		[this]() { SpawnManager::Instance().SpawnObject(new KillerWhaleEnemy(GetRandomSpawnPos())); },
		[this]() { SpawnManager::Instance().SpawnObject(new AmoebaEnemy(GetRandomSpawnPos())); },
		[this]() { SpawnManager::Instance().SpawnObject(new BeholderEnemy(GetRandomSpawnPos())); },
		[this]() { SpawnManager::Instance().SpawnObject(new BubbleEnemy(GetRandomSpawnPos())); },
		[this]() { SpawnManager::Instance().SpawnObject(new ChomperEnemy(GetRandomSpawnPos())); },
		[this]() { SpawnManager::Instance().SpawnObject(new CirclerEnemy(GetRandomSpawnPos())); },
	};

public:
	static EnemyFactory& Instance() {
		static EnemyFactory instance;
		return instance;
	}
};
