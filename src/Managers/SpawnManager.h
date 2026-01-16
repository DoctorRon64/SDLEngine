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

	template<typename T>
	void DestroyAllOfType() {
		size_t count = spawnedObjects.size();

		for(size_t i = 0; i < count; ++i) {
			Object* obj = spawnedObjects.front();
			spawnedObjects.pop();

			if(dynamic_cast<T*>(obj)) {
				obj->Destroy();
			}

			spawnedObjects.push(obj);
		}
	}

	Object* GetSpawnedObject();
	std::queue<Object*> GetSpawnedObjects() const { return spawnedObjects; }

private:
	SpawnManager() = default;
	SpawnManager(SpawnManager&) = delete;
	SpawnManager& operator=(const SpawnManager&) = delete;

	std::queue<Object*> spawnedObjects;
};
