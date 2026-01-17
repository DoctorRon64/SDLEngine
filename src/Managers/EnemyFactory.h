#pragma once
#include "../Objects/Enemies/AmoebaEnemy.h"
#include "../Objects/Enemies/BeholderEnemy.h"
#include "../Objects/Enemies/BubbleEnemy.h"
#include "../Objects/Enemies/ChomperEnemy.h"
#include "../Objects/Enemies/CirclerEnemy.h"
#include "../Objects/Enemies/KillerWhaleEnemy.h"
#include "../Objects/Enemies/BioTitanEnemy.h"
#include "../Objects/Enemies/TorpedoEnemy.h"
#include "../Objects/Enemies/TurboChainsawEnemy.h"
#include "../Objects/Enemies/RoboKrabsEnemy.h"
#include "../Objects/Enemies/NukeEnemy.h"
#include "../Objects/Enemies/MissileEnemy.h"
#include "../Objects/Enemies/DanielsEnemy.h"
#include "../Objects/Enemies/UfoEnemy.h"
#include "../Objects/Enemies/AnnoyerEnemy.h"
#include "../Objects/Enemies/AngrygonEnemy.h"

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
			[this]() { SpawnManager::Instance().SpawnObject(new BioTitanEnemy(GetRandomSpawnPos())); },
			[this]() { SpawnManager::Instance().SpawnObject(new TorpedoEnemy(GetRandomSpawnPos())); },
			[this]() { SpawnManager::Instance().SpawnObject(new TurboChainsawEnemy(GetRandomSpawnPos())); },
			[this]() { SpawnManager::Instance().SpawnObject(new RoboKrabsEnemy(GetRandomSpawnPos())); },
			[this]() { SpawnManager::Instance().SpawnObject(new NukeEnemy(GetRandomSpawnPos())); },
			[this]() { SpawnManager::Instance().SpawnObject(new MissileEnemy(GetRandomSpawnPos())); },
			[this]() { SpawnManager::Instance().SpawnObject(new DanielsEnemy(GetRandomSpawnPos())); },
			[this]() { SpawnManager::Instance().SpawnObject(new UfoEnemy(GetRandomSpawnPos())); },
			[this]() { SpawnManager::Instance().SpawnObject(new AnnoyerEnemy(GetRandomSpawnPos())); },
			[this]() { SpawnManager::Instance().SpawnObject(new AngrygonEnemy(GetRandomSpawnPos())); }
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
