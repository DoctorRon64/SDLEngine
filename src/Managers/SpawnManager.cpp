#include "pch.h"
#include "SpawnManager.h"

void SpawnManager::SpawnObject(Object* obj) {
	spawnedObjects.push(obj);
}

bool SpawnManager::AreObjectsPendingSpawn() {
	return !spawnedObjects.empty();
}

void SpawnManager::ClearSpanwer() {
	while(AreObjectsPendingSpawn()) {
		delete spawnedObjects.front();
		spawnedObjects.pop();
	}
}

Object* SpawnManager::GetSpawnedObject() {
	if(!AreObjectsPendingSpawn()) {
		return nullptr;
	}

	Object* temp = spawnedObjects.front();
	spawnedObjects.pop();
	return temp;
}