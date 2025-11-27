#pragma once
#include <objects/Object.h>

#define spawnerManager Spawner::Instance()

class Spawner {
public:
	static Spawner& Instance() {
		static Spawner spawner;
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

	Object* GetSpawnedObject() {
		if(!AreObjectsPendingSpawn()) {
			return nullptr;
		}

		Object* temp = spawnedObjs.front();
		spawnedObjs.pop();
		return temp;
	}

private:
	Spawner() = default;
	Spawner(Spawner&) = delete;
	Spawner& operator=(const Spawner&) = delete;

	std::queue<Object*> spawnedObjs;
};
