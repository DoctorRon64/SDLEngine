#include "ImageRenderer.h"
#include <SDL3_image/SDL_image.h>
#include <cassert>

void ImageRenderer::LoadTexture(const std::string _texturePath, SDL_Renderer* _renderer) {
	texture = IMG_LoadTexture(_renderer, _texturePath.c_str());
	assert(texture != nullptr && "Failed to load texture");

	sourceRect = { 0.0f, 0.0f, (float)texture->w, (float)texture->h };
}

void ImageRenderer::Update() {
	//does nothing
	//could update shaders
}

void ImageRenderer::Render(SDL_Renderer* _renderer) {
	SDL_RenderTexture(_renderer, texture, &sourceRect, &destinationRect);
}