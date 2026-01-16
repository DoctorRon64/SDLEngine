#pragma once
#include "../Objects/Enemies/AmoebaEnemy.h"
#include "../Objects/Enemies/BeholderEnemy.h"
#include "../Objects/Enemies/BubbleEnemy.h"
#include "../Objects/Enemies/ChomperEnemy.h"
#include "../Objects/Enemies/CirclerEnemy.h"
#include "../Objects/Enemies/KillerWhaleEnemy.h"
#include "../Objects/Enemies/BioTitanEnemy.h"

class EnemyFactory {
public:
	using SpawnFunction = std::function<void()>;

private:
	EnemyFactory() {
		spawnFunctions = { {
			[this]() { SpawnManager::Instance().SpawnObject(new KillerWhaleEnemy(GetRandomSpawnPos())); },
			[this]() { SpawnManager::Instance().SpawnObject(new AmoebaEnemy(GetRandomSpawnPos())); },
			[this]() { SpawnManager::Instance().SpawnObject(new BeholderEnemy(GetRandomSpawnPos())); },
			[this]() { SpawnManager::Instance().SpawnObject(new BubbleEnemy(GetRandomSpawnPos())); },
			[this]() {
				Vector2 pos = GetRandomSpawnPos();
				ChomperEnemy::SpawnLine(pos.x);
			},
			[this]() { SpawnManager::Instance().SpawnObject(new CirclerEnemy(GetRandomSpawnPos())); },
			[this]() { SpawnManager::Instance().SpawnObject(new BioTitanEnemy(GetRandomSpawnPos())); }
		} };
	}

	~EnemyFactory() = default;
	EnemyFactory(const EnemyFactory&) = delete;
	EnemyFactory& operator=(const EnemyFactory&) = delete;

	Vector2 GetRandomSpawnPos() {
		return {
			Randomness::Range(RenderManager::GetInstance()->WINDOW_WIDTH / 2.f,RenderManager::GetInstance()->WINDOW_WIDTH),
			Randomness::Range(0.f, RenderManager::GetInstance()->WINDOW_HEIGHT)
		};
	}

	std::array<SpawnFunction, ENEMY_ID_COUNT> spawnFunctions;

public:
	static EnemyFactory& Instance() {
		static EnemyFactory instance;
		return instance;
	}

	const std::array<SpawnFunction, ENEMY_ID_COUNT>& GetSpawnFunctions() const {
		return spawnFunctions;
	}
};
