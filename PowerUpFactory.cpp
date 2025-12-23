#include "pch.h"
#include "PowerUpFactory.h"

PowerUp* PowerUpFactory::Create(int id) {
	switch(id) {
		case 1:
		return new PowerUpA();
		case 2:
		return new PowerUpB();
		default:
		return nullptr;
	}
}