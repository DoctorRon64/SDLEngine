#include "pch.h"
#include "SceneManager.h"

bool SceneManager::AddScene(std::string _name, Scene* _scene) {
	if(scenes.find(_name) == scenes.end()) {
		scenes.emplace(_name, _scene);
		return true;
	}

	return false;
}

Scene* SceneManager::GetScene(std::string _name) {
	if(scenes.find(_name) != scenes.end())
		return scenes[_name];

	return nullptr;
}

bool SceneManager::InitFirstScene(std::string _name) {
	if(scenes.find(_name) != scenes.end()) {
		currentScene = scenes[_name];
		currentScene->OnEnter();
		return true;
	}

	return false;
}

bool SceneManager::SetNextScene(std::string _name) {
	if(scenes.find(_name) == scenes.end()) {
		return false;
	}

	nextScene = _name;
	return true;
}

void SceneManager::UpdateCurrentScene() {
	if(nextScene != " ") {
		currentScene->OnExit();
		currentScene = scenes[nextScene];
		currentScene->OnEnter();
		nextScene = " ";
	}

	currentScene->OnUpdate();
}