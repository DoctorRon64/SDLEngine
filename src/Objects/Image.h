#pragma once
#include "Object.h"

class Image : public Object {
public:
	Image(std::string _texturePath, Vector2 _sourceOffset, Vector2 _sourceSize) : Object() {
		renderer = new ImageRenderer(transform, _texturePath, _sourceOffset, _sourceSize);
		renderer->LoadTexture(_texturePath, renderManager->GetRenderer());
		SetTextureSize(_sourceSize);
		renderer->SetDestinationRect({ transform->position.x, transform->position.y, textureSize.x, textureSize.y });
	}
};