#pragma once
#include "Components/Transform.h"
#include "Renderers/Renderer.h"

class Object {
private: bool isPendingDestroy = false;
protected:
	Renderer* renderer = nullptr;
	Transform* transform;
	Vector2 textureSize = Vector2(300.0f, 380.0f);
public:
	Object() {
		transform = new Transform();
		//renderer->SetDestinationRect({ transform->position.x, transform->position.y, textureSize.x, textureSize.y });
	}
	~Object() {
		delete transform;
		transform = nullptr;
		delete renderer;
		renderer = nullptr;
	}
	virtual void Update() {
		renderer->Update(0.02f);
	}
	virtual void Render() {
		renderer->Render();
	}
	Transform* GetTransform() { return transform; }
	bool IsPendingDestroy() const {
		return isPendingDestroy;
	} virtual void Destroy() {
		isPendingDestroy = true;
	}
};