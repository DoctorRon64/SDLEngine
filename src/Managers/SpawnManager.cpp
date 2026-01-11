#include "pch.h"
#include "SpawnManager.h"

void SpawnManager::SpawnObject(Object* obj) {
	spawnedObjs.push(obj);
}

bool SpawnManager::AreObjectsPendingSpawn() {
	return !spawnedObjs.empty();
}

void SpawnManager::ClearSpanwer() {
	while(AreObjectsPendingSpawn()) {
		delete spawnedObjs.front();
		spawnedObjs.pop();
	}
}

Object* SpawnManager::GetSpawnedObject() {
	if(!AreObjectsPendingSpawn()) {
		return nullptr;
	}

	Object* temp = spawnedObjs.front();
	spawnedObjs.pop();
	return temp;
}