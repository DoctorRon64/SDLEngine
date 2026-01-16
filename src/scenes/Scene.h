#pragma once
#include <Objects/Object.h>
class Scene {
protected:
	std::vector<Object* > ui;
	std::vector<Object* > objects;

	void UpdateUI();
public:
	Scene() = default;
	virtual void OnEnter() = 0;

	virtual void OnExit();
	virtual void OnUpdate();
	virtual void Render();
};