#pragma once
#include <Scenes/Scene.h>

enum class SceneState {
	NONE,
	SPLASH,
	MENU,
	LEVEL_SELECT,
	GAMEPLAY,
	RANKING
};

class SceneManager {
private:
	SceneManager() = default;
	SceneManager(SceneManager&) = delete;
	SceneManager& operator =(const SceneManager&) = delete;
	~SceneManager() = default;

	std::unordered_map <SceneState, Scene*> scenes;
	Scene* currentScene = nullptr;
	SceneState nextScene = SceneState::NONE;

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
