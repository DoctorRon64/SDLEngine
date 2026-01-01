#pragma once
#include "../components/Collidable.h"
#include "Objects/Image.h"

class Actor : public Image, public Collidable {
protected:
	int maxHealth;
	int health;

public:
	Actor(
		std::string _texturePath,
		Vector2 _sourceOffset = Vector2(0, 0),
		Vector2 _sourceSize = Vector2(400.f, 400.f),
		int _maxHealth = 100,
		int _health = 0
	)
		: Image(_texturePath, _sourceOffset, _sourceSize),
		maxHealth(_maxHealth),
		health(_health), Collidable(this, rbComp) {}

	virtual ~Actor() = default;

	std::function<void(int current, int max)> OnHealthChanged;
	void Damage(int amount) {
		health -= amount;
		OnHealthChangedEvent();
	}
	void Heal(int amount) {
		health += amount;
		OnHealthChangedEvent();
	}
	void HealToMax() {
		health = maxHealth;
		OnHealthChangedEvent();
	}
	void OnHealthChangedEvent() {
		if(OnHealthChanged) OnHealthChanged(health, maxHealth);
	}

	bool IsDead() const { return health <= 0; }
};