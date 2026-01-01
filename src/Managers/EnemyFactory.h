#pragma once
#include "../Objects/custom/Enemy.h"
#include "../Objects/Enemies/KillerWhaleEnemy.h"
class EnemyFactory
{
	using SpawnFunction = std::function<void()>;
private:
	EnemyFactory() = default;
	~EnemyFactory() = default;
	EnemyFactory(const EnemyFactory&) = delete;
	EnemyFactory& operator=(const EnemyFactory&) = delete;

public:
	const SpawnFunction spawnFunctions[ENEMY_ID_COUNT] = {
		[]() { SpawnManager::Instance().SpawnObject(new KillerWhaleEnemy({ 
			(float)RenderManager::GetInstance()->WINDOW_WIDTH, 
			(float)RenderManager::GetInstance()->WINDOW_HEIGHT / 2
			})); },
		[]() { SpawnManager::Instance().SpawnObject(new KillerWhaleEnemy({
			(float)RenderManager::GetInstance()->WINDOW_WIDTH,
			(float)RenderManager::GetInstance()->WINDOW_HEIGHT / 2
			})); },
		[]() { SpawnManager::Instance().SpawnObject(new KillerWhaleEnemy({
			(float)RenderManager::GetInstance()->WINDOW_WIDTH,
			(float)RenderManager::GetInstance()->WINDOW_HEIGHT / 2
			})); },
		[]() { SpawnManager::Instance().SpawnObject(new KillerWhaleEnemy({
			(float)RenderManager::GetInstance()->WINDOW_WIDTH,
			(float)RenderManager::GetInstance()->WINDOW_HEIGHT / 2
			})); },
		[]() { SpawnManager::Instance().SpawnObject(new KillerWhaleEnemy({
			(float)RenderManager::GetInstance()->WINDOW_WIDTH,
			(float)RenderManager::GetInstance()->WINDOW_HEIGHT / 2
			})); }
	};

public:
	static EnemyFactory& Instance() {
		static EnemyFactory instance;
		return instance;
	}
};

