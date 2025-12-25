#pragma once
#include "PowerUp.h"

enum class PowerupId {
	SCORE = 0,
	CANNONS_ENERGY = 1,
	LASER_ENERGY = 2,
	ENGINES_ENERGY = 3,
	SHIELD_ENERGY = 4,
	TWIN_TURRETS = 5
};

class PowerUpFactory {
public:
	PowerUp* Create(PowerupId id);
};
