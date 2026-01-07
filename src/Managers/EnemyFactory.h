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

public:
	const SpawnFunction spawnFunctions[ENEMY_ID_COUNT] = {
		[]() { SpawnManager::Instance().SpawnObject(new KillerWhaleEnemy({
			(float)RenderManager::GetInstance()->WINDOW_WIDTH,
			(float)RenderManager::GetInstance()->WINDOW_HEIGHT / 2
			})); },
		[]() { SpawnManager::Instance().SpawnObject(new AmoebaEnemy({
			(float)RenderManager::GetInstance()->WINDOW_WIDTH,
			(float)RenderManager::GetInstance()->WINDOW_HEIGHT / 2
			})); },
		[]() { SpawnManager::Instance().SpawnObject(new BeholderEnemy({
			(float)RenderManager::GetInstance()->WINDOW_WIDTH,
			(float)RenderManager::GetInstance()->WINDOW_HEIGHT / 2
			})); },
		[]() { SpawnManager::Instance().SpawnObject(new BubbleEnemy({
			(float)RenderManager::GetInstance()->WINDOW_WIDTH,
			(float)RenderManager::GetInstance()->WINDOW_HEIGHT / 2
			})); },
		[]() { SpawnManager::Instance().SpawnObject(new ChomperEnemy({
			(float)RenderManager::GetInstance()->WINDOW_WIDTH,
			(float)RenderManager::GetInstance()->WINDOW_HEIGHT / 2
			})); },
		[]() { SpawnManager::Instance().SpawnObject(new CirclerEnemy({
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
