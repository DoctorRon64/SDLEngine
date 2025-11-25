#pragma once
#include "Objects/TestObject.h"
#include "scenes/Scene.h"

class GameplayScene : public Scene {
public:
	GameplayScene() = default;
	void OnEnter() override {
		TestObject* test1 = new TestObject();
		objects.push_back(test1);
		TestObject* test2 = new TestObject();
		objects.push_back(test2);
	}

	void OnExit() override { Scene::OnExit(); }
	void OnUpdate() override { Scene::OnUpdate(); }
	void Render() override { Scene::Render(); }
};