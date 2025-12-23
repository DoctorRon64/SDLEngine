#pragma once
#include <objects/Object.h>

#define spawnManager SpawnManager::Instance()

class SpawnManager {
public:
	static SpawnManager& Instance() {
		static SpawnManager spawner;
		return spawner;
	}

	void SpawnObject(Object* obj) {
		spawnedObjs.push(obj);
	}

	bool AreObjectsPendingSpawn() {
		return !spawnedObjs.empty();
	}

	void ClearSpanwer() {
		while(AreObjectsPendingSpawn()) {
			delete spawnedObjs.front();
			spawnedObjs.pop();
		}
	}

	std::queue<Object*> GetSpawnedObjects() const {
		return spawnedObjs;
	}

	Object* GetSpawnedObject() {
		if(!AreObjectsPendingSpawn()) {
			return nullptr;
		}

		Object* temp = spawnedObjs.front();
		spawnedObjs.pop();
		return temp;
	}

private:
	SpawnManager() = default;
	SpawnManager(SpawnManager&) = delete;
	SpawnManager& operator=(const SpawnManager&) = delete;

	std::queue<Object*> spawnedObjs;
};
