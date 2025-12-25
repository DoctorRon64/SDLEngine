#include "pch.h"
#include "PowerUpFactory.h"
#include "ScorePowerUp.h"
#include "CannonEnergyPowerUp.h"
#include "LaserEnergyPowerUp.h"
#include "EngineEnergyPowerUp.h"
#include "ShieldEnergyPowerUp.h"
#include "TwinTurretsPowerUp.h"

PowerUp* PowerUpFactory::Create(PowerupId id) {
	switch(id) {
		case PowerupId::SCORE:
			return new ScorePowerUp();
		case PowerupId::CANNONS_ENERGY:
			return new CannonEnergyPowerUp();
		case PowerupId::LASER_ENERGY:
			return new LaserEnergyPowerUp();
		case PowerupId::ENGINES_ENERGY:
			return new EngineEnergyPowerUp();
		case PowerupId::SHIELD_ENERGY:
			return new ShieldEnergyPowerUp();
		case PowerupId::TWIN_TURRETS:
			return new TwinTurretsPowerUp();
	}
}