#pragma once
#include "../Image.h"
class Decoration :
    public Image
{
public:
	Decoration(std::string _texturePath, Vector2 _sourceOffset = Vector2(0, 0), Vector2 _sourceSize = Vector2(400.f, 400.f))
		: Image(_texturePath, _sourceOffset, _sourceSize) {}

	void Update() override {
		Image::Update();
		if (transform->position.x > RenderManager::GetInstance()->WINDOW_WIDTH + 5 || transform->position.x < -transform->GetSize().x - 5) {
			Destroy();
		}
	}
};

