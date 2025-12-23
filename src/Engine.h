#pragma once
#include "Objects/Object.h"

class Engine {
public:
	Engine();
	~Engine();
	void Init();
	void LoadAssets();
	void HandleEvents();
	void Update();
	void Render();
	bool IsRunning() const { return isRunning; }
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<Object*> gameObjects;
};
