#pragma once
#include "../AnimatedImage.h"
#include "../../components/Collidable.h"
#include <unordered_set>
#include <Math/AABB.h>
#include <Utils/config.h>

class Explosion :
	public AnimatedImage, public Collidable {
public:
	Explosion() :
		AnimatedImage(EXPLOSION_SPRITE_PATH, { 0.f, 0.f }, { 100.f, 100.f }, 49, 13, 100.f, 100.f, 5, false),
		Collidable(rbComp) {
		transform->scale = Vector2(3.f, 3.f);
		rbComp->AddCollider(new AABB(transform->position, transform->GetSize()));
	}

	virtual void Update() override {
		AnimatedImage::Update();
	}

	void OnCollision(Collidable* other) override {
		Object* obj = dynamic_cast<Object*>(other);
		if(!obj) return;
		if(pushedObjects.find(obj) != pushedObjects.end()) return;

		RigidBody* otherBody = obj->GetRigidBody();
		if(!otherBody) return;

		Vector2 center = transform->position + transform->GetSize() * 0.5f;
		Vector2 otherCenter = obj->GetTransform()->position + obj->GetTransform()->GetSize() * 0.5f;
		Vector2 dir = otherCenter - center;
		if(dir.LengthSquared() < 0.001f) return;

		dir.Normalize();
		otherBody->AddForce(dir * EXPLOSION_PUSH_FORCE);
		pushedObjects.insert(obj);
	}

private:
	std::unordered_set<Object*> pushedObjects;
};
