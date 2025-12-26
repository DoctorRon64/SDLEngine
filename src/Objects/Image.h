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

	//TODO delete this
	virtual void SetScaleCentered(const Vector2& newScale) {
		Vector2 oldSize = transform->GetSize();
		Vector2 newSize = transform->GetSize() * newScale;

		transform->position -= (newSize - oldSize) * 0.5f;
		transform->scale = newScale;
	}
};