#include "RenderManager.h"
#include <SDL3_image/SDL_image.h>
#include <cassert>

RenderManager::RenderManager() {
	for(std::map<std::string, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it) {
		if(it->second != nullptr) {
			SDL_DestroyTexture(it->second);
		}
	}
}

void RenderManager::InitSDL() {
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		throw SDL_GetError();
	}
}

void RenderManager::CreateWindowAndRender() {
	if(!SDL_CreateWindowAndRenderer(windowTitle.c_str(), WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		throw SDL_GetError();
	}
}

void RenderManager::Terminate() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void RenderManager::RenderScreen() {
	SDL_RenderPresent(renderer);
}

void RenderManager::ClearScreen() {
	SDL_RenderClear(renderer);
}

void RenderManager::Init() {
	try {
		InitSDL();
		CreateWindowAndRender();
	}
	catch(std::exception& exception) {
		std::cout << "Error: " << exception.what();
		Terminate();
		return;
	}

	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0xff);
}

void RenderManager::LoadTexture(const std::string path) {
	if(textures.find(path) != textures.end()) return;

	SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
	if(!texture) {
		throw SDL_GetError();
	}
	assert(texture);
	assert(textures[path]);

	textures[path] = texture;
}

SDL_Texture* RenderManager::GetTexture(const std::string& textureName) {
	if(textures.find(textureName) != textures.end()) {
		return textures[textureName];
	}
	return nullptr;
}