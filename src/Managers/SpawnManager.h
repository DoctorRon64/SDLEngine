#pragma once
#include <objects/Object.h>

class SpawnManager {
public:
	static SpawnManager& Instance() {
		static SpawnManager spawner;
		return spawner;
	}

	void SpawnObject(Object* obj);
	bool AreObjectsPendingSpawn();
	void ClearSpanwer();

	Object* GetSpawnedObject();
	std::queue<Object*> GetSpawnedObjects() const { return spawnedObjs; }

private:
	SpawnManager() = default;
	SpawnManager(SpawnManager&) = delete;
	SpawnManager& operator=(const SpawnManager&) = delete;

	std::queue<Object*> spawnedObjs;
};
