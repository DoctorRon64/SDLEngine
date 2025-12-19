#pragma once
#include "Components/Transform.h"
#include "Renderers/Renderer.h"

class ImageRenderer : public Renderer {
public:
	ImageRenderer(Transform* _transform, std::string _resourcePath, Vector2 _sourceOffset, Vector2 _sourceSize)
		: Renderer(_transform, _resourcePath),
		resourcePath(_resourcePath),
		sourceOffset(_sourceOffset),
		sourceSize(_sourceSize) {}

	virtual void Update(float _deltaTime) override;
	virtual void Render() override;

	Vector2 GetTextureSize() const { return textureSize; }

private:
	SDL_Texture* texture = nullptr;
	std::string resourcePath;
	Vector2 textureSize{ 0, 0 };
	Vector2 sourceOffset;
	Vector2 sourceSize;
};