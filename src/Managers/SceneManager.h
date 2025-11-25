#pragma once
#include <Scenes/Scene.h>
#define sceneManager SceneManager::GetInstance()

class SceneManager {
private:
	SceneManager() = default;
	SceneManager(SceneManager&) = delete;
	SceneManager& operator =(const SceneManager&) = delete;
	~SceneManager() = default;

	std::unordered_map <std::string, Scene*> scenes;
	Scene* currentScene = nullptr;
	std::string nextScene = " ";

public:
	static SceneManager* GetInstance() {
		static SceneManager instance;
		return &instance;
	}

	bool AddScene(std::string _name, Scene* _scene);
	Scene* GetScene(std::string _name);
	bool InitFirstScene(std::string _name);
	Scene* GetCurrentScene() const { return currentScene; }
	bool SetNextScene(std::string _name);
	void UpdateCurrentScene();
};