#pragma once
#include <Scenes/Scene.h>
#define sceneManager SceneManager::GetInstance()

enum SceneState { NONE, MENU, GAMEPLAY };

class SceneManager {
private:
	SceneManager() = default;
	SceneManager(SceneManager&) = delete;
	SceneManager& operator =(const SceneManager&) = delete;
	~SceneManager() = default;

	std::unordered_map <SceneState, Scene*> scenes;
	Scene* currentScene = nullptr;
	SceneState nextScene = NONE;

public:
	static SceneManager* GetInstance() {
		static SceneManager instance;
		return &instance;
	}

	bool AddScene(SceneState _name, Scene* _scene);
	Scene* GetScene(SceneState _name);
	bool InitFirstScene(SceneState _name);
	Scene* GetCurrentScene() const { return currentScene; }
	bool SetNextScene(SceneState _name);
	void UpdateCurrentScene();
};