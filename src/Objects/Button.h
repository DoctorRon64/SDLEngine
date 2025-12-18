#pragma once
#include "Image.h"

class Button : public Image {
public:
	typedef std::function <void()> OnClick;

	Button(OnClick _onClick) : Image("res/btn.png", Vector2(0.f, 0.f), Vector2(3448.f, 1369.f)) {
		onClick = _onClick;

		transform->position = Vector2(200.f, 200.f);
		transform->scale = Vector2(.05f, .05f);

		GetRigidBody()->AddCollider(new AABB(transform->position, transform->size));
	}

	virtual void Render() override {
		Object::Render();
	}

	virtual void Update() override {
		if(!isHovered && GetRigidBody()->CheckOverlappingPoint({ (float)inputManager->GetMouseX() , (float)inputManager->GetMouseY() })) {
			OnHoverEnter();
		}
		else if(isHovered && !GetRigidBody()->CheckOverlappingPoint({ (float)inputManager->GetMouseX() , (float)inputManager->GetMouseY() })) {
			OnHoverExit();
		}
		else if(isHovered && inputManager->GetLeftClick()) {
			OnClicked();
		}

		Object::Update();
	}

private:
	bool isHovered = false;
	OnClick onClick;

	void OnHoverEnter();
	void OnHoverExit();
	void OnClicked();
};
