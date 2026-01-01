#pragma once
#include "Objects/Image.h"

class Actor : public Image {
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
		health(_health) {}

	virtual ~Actor() = default;

	void Damage(int amount) { health -= amount; }
	void Heal(int amount) { health += amount; }
	void HealToMax() { health = maxHealth; }
	bool IsDead() const { return health <= 0; }
};