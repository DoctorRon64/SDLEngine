#pragma once
#include "GameObject.h"
#include <SDL3/SDL.h>
#include <vector>

class Engine
{
public:
	Engine() = default;
	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Terminate();

	bool IsRunning() const { return isRunning; }

private:
	void InitSDL();
	void CreateWindowAndRenderer();

	bool isRunning;
	const std::size_t windowX = 16 * 100;
	const std::size_t windowY = 9 * 100;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<GameObject> gameObjects;
};
