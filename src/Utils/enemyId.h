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

	throw std::runtime_error("Unknown enemy type: " + s);
}
