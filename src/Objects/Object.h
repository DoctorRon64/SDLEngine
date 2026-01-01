#pragma once
#include "Components/Transform.h"
#include <Components/Rigidbody.h>

class Object {
private:
	bool isPendingDestroy = false;
protected:
	Renderer* renderer = nullptr;
	Transform* transform = nullptr;
	RigidBody* rbComp = nullptr;
	short layer = 0;

public:
	Object() {
		transform = new Transform();
		rbComp = new RigidBody(transform);
	}
	virtual ~Object() {
		delete transform;
		delete renderer;
		delete rbComp;

		transform = nullptr;
		renderer = nullptr;
		rbComp = nullptr;
	}

	virtual void Update() {
		float deltaTime = TimeManager::GetInstance()->GetDeltaTime();
		if(rbComp != nullptr) {
			rbComp->Update(deltaTime);
		}
		renderer->Update(deltaTime);
	}
	virtual void Render() {
		if(!renderer) return;
		renderer->Render();
	}
	virtual void Destroy() {
		if(isPendingDestroy) return;
		isPendingDestroy = true;
	}
	void SetLayer(const short& _value) { layer = _value; }

	Transform* GetTransform() const { return transform; }
	bool IsPendingDestroy() const { return isPendingDestroy; }
	RigidBody* GetRigidBody() const { return rbComp; }
	short GetLayer() const { return layer; }
	Renderer* GetRenderer() const { return renderer; }
	virtual void OnCollision(Object* other) {}
};