#pragma once
#include "Image.h"
#include "Text.h"
#include "../Renderers/ButtonRenderer.h"

class Button : public Image {
public:
	using OnClick = std::function<void()>;

	Button(OnClick _onClick, Text* _label = new Text(" "))
		: Image("res/btn.png", { 0, 0 }, { 3448.f, 1369.f }), onClick(_onClick), label(_label) {

		renderer = new ButtonRenderer(transform, "res/btn.png", { 0, 0 }, { 3448.f, 1369.f });

		transform->scale = Vector2(.1f, .1f);

		collider = new AABB({ 0.f, 0.f }, transform->GetSize());

		Vector2 topLeft = { transform->position.x, transform->position.y };
		collider->SetTopLeft(topLeft);
		collider->SetSize(transform->GetSize());
		GetRigidBody()->AddCollider(collider);
	}

	void Update() override {

		label->GetTransform()->position = transform->position + transform->GetSize() / 4;

		Vector2 mousePos = {
			(float)InputManager::GetInstance()->GetMouseX(),
			(float)InputManager::GetInstance()->GetMouseY()
		};

		bool hovering = collider->CheckOverlappingPoint(mousePos);

		if(hovering && !isHovered) {
			OnHoverEnter();
		}
		else if(!hovering && isHovered) {
			OnHoverExit();
		}

		if(isHovered && InputManager::GetInstance()->GetLeftClick()) {
			OnClicked();
			InputManager::GetInstance()->LeftClickProcessed();
		}

		Object::Update();
	}

private:
	const float hoverScaleFactor = 1.1f;
	bool isHovered = false;
	AABB* collider = nullptr;
	OnClick onClick;
	Text* label;
	Vector2 labelStartScale;

	void OnHoverEnter() {
		transform->scale = transform->scale * hoverScaleFactor;
		label->GetTransform()->scale = label->GetTransform()->scale * hoverScaleFactor;
		//SetScaleCentered(transform->scale * hoverScaleFactor);
		AudioManager::GetInstance()->PlaySound("res/audio/sfx/ui_hover.wav");

		isHovered = true;
	}

	void OnHoverExit() {
		transform->scale = transform->scale / hoverScaleFactor;
		label->GetTransform()->scale = label->GetTransform()->scale / hoverScaleFactor;
		isHovered = false;
	}

	void OnClicked() {
		AudioManager::GetInstance()->PlaySound("res/audio/sfx/ui_select.wav");
		onClick();
	}
};
