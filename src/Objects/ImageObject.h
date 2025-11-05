#pragma once
#include "Object.h"
#include "Renderers/ImageRenderer.h"
#include <Managers/RenderManager.h>
#include <Math/Vector2.h>
#include <string>

class ImageObject : public Object {
public:
	ImageObject(std::string _texturePath, Vector2 _sourceOffset, Vector2 _sourceSize) : Object() {
		renderer = new ImageRenderer(transform, _texturePath, _sourceOffset, _sourceSize);
		renderer->LoadTexture(_texturePath, renderManager->GetRenderer());
		renderer->SetDestinationRect({ transform->position.x, transform->position.y, textureSize.x, textureSize.y });
	}
};
