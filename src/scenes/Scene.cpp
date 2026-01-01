#include "pch.h"
#include "Scene.h"

void Scene::OnExit() {
	SpawnManager::Instance().ClearSpanwer();

	for(Object* o : objects) {
		delete o;
	}
	objects.clear();

	for(Object* o : ui) {
		delete o;
	}
	ui.clear();
}

void Scene::OnUpdate() {
	while(SpawnManager::Instance().AreObjectsPendingSpawn()) {
		objects.push_back(SpawnManager::Instance().GetSpawnedObject());
	}

	for(Object* o : objects) {
		o->Update();
	}

	for(Object* u : ui) {
		u->Update();
	}

	CollisionManager::Instance().CheckCollisions();

	for(int i = objects.size() - 1; i >= 0; i--) {
		if(objects[i]->IsPendingDestroy()) {
			delete objects[i];
			objects.erase(objects.begin() + i);
		}
	}

	for(int i = ui.size() - 1; i >= 0; i--) {
		if(ui[i]->IsPendingDestroy()) {
			delete ui[i];
			ui.erase(ui.begin() + i);
		}
	}
}

void Scene::Render() {
	for(Object* o : objects) {
		o->Render();
	}
	for(Object* u : ui) {
		u->Render();
	}
}