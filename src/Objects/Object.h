#pragma once
#include "Components/Transform.h"
#include <Components/Rigidbody.h>

class Object {
private: bool isPendingDestroy = false;
protected:
	Renderer* renderer = nullptr;
	Transform* transform = nullptr;
	RigidBody* rbComp = nullptr;
	Vector2 textureSize = Vector2(300.0f, 380.0f);
public:
	Object() {
		transform = new Transform();
		rbComp = new RigidBody(transform);
	}
	~Object() {
		delete transform;
		transform = nullptr;
		delete renderer;
		renderer = nullptr;
		delete rbComp;
		rbComp = nullptr;
	}
	virtual void Update() {
		float deltaTime = timeManager->GetDeltaTime();
		if(rbComp != nullptr) {
			rbComp->Update(deltaTime);
		}
		renderer->Update(deltaTime);
	}
	virtual void Render() { renderer->Render(); }
	Transform* GetTransform() { return transform; }
	bool IsPendingDestroy() const { return isPendingDestroy; }
	virtual void Destroy() { isPendingDestroy = true; }
	virtual void SetTextureSize(const Vector2 _size) { textureSize = _size; }
};