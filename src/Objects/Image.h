#pragma once
#include "Object.h"

class Image : public Object {
public:
	Image(std::string _texturePath, Vector2 _sourceOffset = Vector2(0, 0), Vector2 _sourceSize = Vector2(400.f, 400.f))
		: Object() {
		//renderManager->LoadTexture(_texturePath); TODO LATER Would be nice if all Images load there textures here instead of defining it at Start
		SDL_Texture* tex = renderManager->GetTexture(_texturePath);

		float textureWidth = 0;
		float textureHeight = 0;
		SDL_GetTextureSize(tex, &textureWidth, &textureHeight);
		textureSize = _sourceSize.x > 0 ? _sourceSize : Vector2(textureWidth, textureHeight);

		renderer = new ImageRenderer(transform, _texturePath, _sourceOffset, _sourceSize);
		//transform->size = _sourceSize;

		/*renderer->SetDestinationRect({
			static_cast<float>(transform->position.x),
			static_cast<float>(transform->position.y),
			static_cast<float>(_sourceSize.x * transform->scale.x),
			static_cast<float>(_sourceSize.y * transform->scale.y)
		});*/
	}
};