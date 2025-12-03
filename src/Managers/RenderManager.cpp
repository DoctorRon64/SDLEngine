#include "pch.h"
#include "RenderManager.h"

RenderManager::~RenderManager() {
	//TODO remove code
	//for(std::map<std::string, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it) {
	//	if(it->second != nullptr) {
	//		SDL_DestroyTexture(it->second);
	//	}
	//}

	for(std::map<std::string, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); it++) {
		SDL_DestroyTexture(it->second);
		it->second = nullptr;
	}

	for(std::map<std::string, TTF_Font*>::iterator it = fonts.begin(); it != fonts.end(); it++) {
		TTF_CloseFont(it->second);
		it->second = nullptr;
	}
}

void RenderManager::InitSDL() {
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		throw SDL_GetError();
	}

	if(!TTF_Init()) {
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

void RenderManager::LoadTexture(const std::string& path) {
	auto it = textures.find(path);
	if(it != textures.end()) return;

	if(SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str())) {
		textures.emplace(path, texture);
	}
	else {
		throw std::runtime_error(SDL_GetError());
	}
}

SDL_Texture* RenderManager::GetTexture(const std::string& textureName) {
	if(textures.find(textureName) != textures.end()) {
		return textures[textureName];
	}
	return nullptr;
}

void RenderManager::LoadFont(std::string _path) {
	if(fonts.find(_path) != fonts.end())
		return;
	fonts[_path] = TTF_OpenFont(_path.c_str(), 24);
}

TTF_Font* RenderManager::GetFont(std::string _path) {
	if(fonts.find(_path) != fonts.end()) {
		return fonts[_path];
	}

	return nullptr;
}