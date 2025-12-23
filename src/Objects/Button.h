#pragma once
#include "Image.h"

class Button : public Image {
public:
	using OnClick = std::function<void()>;

	Button(OnClick _onClick)
		: Image("res/btn.png", { 0, 0 }, { 3448.f, 1369.f }), onClick(_onClick) {
		transform->scale = Vector2(.1f, .1f);

		collider = new AABB({ 0.f, 0.f }, transform->GetSize());

		Vector2 topLeft = { transform->position.x, transform->position.y };
		collider->SetTopLeft(topLeft);
		collider->SetSize(transform->GetSize());
		GetRigidBody()->AddCollider(collider);
	}

	void Update() override {
		Vector2 mousePos = {
			(float)inputManager->GetMouseX(),
			(float)inputManager->GetMouseY()
		};

		bool hovering = collider->CheckOverlappingPoint(mousePos);

		if(hovering && !isHovered) {
			OnHoverEnter();
		}
		else if(!hovering && isHovered) {
			OnHoverExit();
		}

		if(isHovered && inputManager->GetLeftClick()) {
			OnClicked();
		}

		Object::Update();
	}

private:
	const float hoverScaleFactor = 1.1f;
	bool isHovered = false;
	AABB* collider = nullptr;
	OnClick onClick;

	void OnHoverEnter() {
		transform->scale = transform->scale * hoverScaleFactor;
		//SetScaleCentered(transform->scale * hoverScaleFactor);
		audioManager->PlaySound("res/audio/sfx/ui_hover.wav");

		isHovered = true;
	}

	void OnHoverExit() {
		transform->scale = transform->scale / hoverScaleFactor;
		isHovered = false;
	}

	void OnClicked() {
		audioManager->PlaySound("res/audio/sfx/ui_select.wav");
		onClick();
	}
};
