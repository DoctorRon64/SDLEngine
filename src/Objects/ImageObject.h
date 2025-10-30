#pragma once

#include "Object.h"
#include "Renderers/ImageRenderer.h"
class ImageObject : public Object {
public:
	ImageObject(const std::string _texturePath, SDL_Renderer* _renderer) {
		renderer = new ImageRenderer();
		renderer->LoadTexture(_texturePath, _renderer);
		renderer->SetDestinationRect({ position.x, position.y, textureSize.x, textureSize.y });
	}
	~ImageObject() {
		delete renderer;
	}
};
