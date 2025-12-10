#include "pch.h"
#include "Scene.h"

void Scene::OnExit() {
	spawnerManager.ClearSpanwer();

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

	while(spawnerManager.AreObjectsPendingSpawn()) {
		objects.push_back(spawnerManager.GetSpawnedObject());
	}

	//std::sort(objects.begin(), objects.end(),
	//[](Object* a, Object* b) {
	//	return a->GetLayer() < b->GetLayer();
	//});

	for(Object* o : objects) {
		o->Update();
	}

	for(Object* u : ui) {
		u->Update();
	}

	int size = objects.size();
	for(int i = 0; i < size; i++) {
		for(int j = i + 1; j < objects.size(); j++) {
			if(objects[i]->GetRigidBody()->CheckCollision(objects[j]->GetRigidBody())) {
			}
		}
	}

	size = ui.size();
	for(int i = 0; i < size; i++) {
		for(int j = i + 1; j < ui.size(); j++) {
			if(ui[i]->GetRigidBody()->CheckCollision(ui[j]->GetRigidBody())) {
				// ...
			}
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