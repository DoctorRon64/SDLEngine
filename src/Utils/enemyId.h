#pragma once
#include <stdexcept>

enum class EnemyId {
	KILLER_WHALE,
	AMOEBA,
	BEHOLDER,
	BUBBLE,
	CHOMPER,
	CIRCLER,
	BIO_TITAN,
	TORPEDO,
	TURBO_CHAINSAW,
	ROBO_KRABS,
	NUKE,
	MISSILE,
	DANIELS,
	UFO,
	ANNOYER,
	ANGRYGON,
	COUNT
};

inline EnemyId EnemyIdFromString(const std::string& s) {
	if(s == "KILLER_WHALE") return EnemyId::KILLER_WHALE;
	if(s == "AMOEBA") return EnemyId::AMOEBA;
	if(s == "BEHOLDER") return EnemyId::BEHOLDER;
	if(s == "BUBBLE") return EnemyId::BUBBLE;
	if(s == "CHOMPER") return EnemyId::CHOMPER;
	if(s == "CIRCLER") return EnemyId::CIRCLER;
	if(s == "BIO_TITAN") return EnemyId::BIO_TITAN;
	if(s == "TORPEDO") return EnemyId::TORPEDO;
	if(s == "TURBO_CHAINSAW") return EnemyId::TURBO_CHAINSAW;
	if(s == "ROBO_KRABS") return EnemyId::ROBO_KRABS;
	if(s == "NUKE") return EnemyId::NUKE;
	if(s == "MISSILE") return EnemyId::MISSILE;
	if(s == "DANIELS") return EnemyId::DANIELS;
	if(s == "UFO") return EnemyId::UFO;
	if(s == "ANNOYER") return EnemyId::ANNOYER;
	if(s == "ANGRYGON") return EnemyId::ANGRYGON;

	throw std::runtime_error("Unknown enemy type: " + s);
}
