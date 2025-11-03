#pragma once
#include <iostream>
#include <map>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#define renderManager RenderManager::GetInstance()

class RenderManager {
public:
	static RenderManager* GetInstance() {
		static RenderManager instance;
		return &instance;
	}

	const std::string windowTitle = "SDL Engine";
	const unsigned int WINDOW_WIDTH = 800;
	const unsigned int WINDOW_HEIGHT = 800;

	void Init();
	void Terminate();
	void ClearScreen();
	void RenderScreen();

	SDL_Renderer* GetRenderer() const { return renderer; }
	void LoadTexture(const std::string& _texturePath);
	SDL_Texture* GetTexture(const std::string& textureName);

private:
	RenderManager();
	RenderManager(RenderManager&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;
	~RenderManager() {}

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::map<std::string, SDL_Texture*> textures;

	void InitSDL();
	void CreateWindowAndRender();
};
