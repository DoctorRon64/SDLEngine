#pragma once
#include <SDL3/SDL_render.h>
#include <string>
#include "Math/Vector2.h"
#include <Renderers/Renderer.h>

class Object {
protected:
	Vector2 position;
	Renderer* renderer;
	Vector2 textureSize = Vector2(100.0f, 100.0f);
public:
	Object() {
		position = Vector2();
		renderer = nullptr;
	}
	void SetPosition(Vector2 pos) {
		position = pos;
		renderer->SetDestinationRect({ position.x, position.y, textureSize.x, textureSize.y });
	}
	Vector2 GetPosition() const {
		return position;
	}
	void Update() {
		renderer->Update();
	}
	void Render(SDL_Renderer* _renderer) {
		renderer->Render(_renderer);
	}
};