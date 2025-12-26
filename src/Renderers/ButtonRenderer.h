#pragma once
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include <Objects/Text.h>
class ButtonRenderer :
    public ImageRenderer
{
public:
	ButtonRenderer(Transform* _transform, std::string _resourcePath, Vector2 _sourceOffset, Vector2 _sourceSize)
		: ImageRenderer(_transform, _resourcePath, _sourceOffset, _sourceSize) {
	}

	void Update(float _deltaTime) override { 
		ImageRenderer::Update(_deltaTime); 
	}
	void Render() override { 
		ImageRenderer::Render(); 
	}
};

