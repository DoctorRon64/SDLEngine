#pragma once
#include "PowerUp.h"
class PowerUpFactory {
public:
	PowerUp* Create(int id);
};
