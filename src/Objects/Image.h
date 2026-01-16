#pragma once
#include "Object.h"

class Image : public Object {
public:
	Image(std::string _texturePath, Vector2 _sourceOffset = Vector2(0, 0), Vector2 _sourceSize = Vector2(400.f, 400.f))
		: Object() {
		renderer = new ImageRenderer(transform, _texturePath, _sourceOffset, _sourceSize);
		transform->SetSize(_sourceSize);
		renderer->SetDestinationRect({
			static_cast<float>(transform->position.x),
			static_cast<float>(transform->position.y),
			static_cast<float>(_sourceSize.x * transform->scale.x),
			static_cast<float>(_sourceSize.y * transform->scale.y)
		});
	}
};