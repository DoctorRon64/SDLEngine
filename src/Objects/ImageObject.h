#pragma once
#include "Object.h"

class ImageObject : public Object {
public:
	ImageObject(std::string _texturePath, Vector2 _sourceOffset, Vector2 _sourceSize) : Object() {
		renderer = new ImageRenderer(transform, _texturePath, _sourceOffset, _sourceSize);
		renderer->LoadTexture(_texturePath, renderManager->GetRenderer());
		auto texture = renderManager->GetTexture(_texturePath);
		SetTextureSize(Vector2(texture->w, texture->h));
		renderer->SetDestinationRect({ transform->position.x, transform->position.y, textureSize.x, textureSize.y });
	}
};