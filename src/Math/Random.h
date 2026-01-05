#pragma once
#include <random>

namespace Random {
	inline std::mt19937& Generator() {
		static std::mt19937 gen{ std::random_device{}() };
		return gen;
	}

	inline int Range(int min, int max) {
		std::uniform_int_distribution<int> dist(min, max);
		return dist(Generator());
	}

	inline float Range(float min, float max) {
		std::uniform_real_distribution<float> dist(min, max);
		return dist(Generator());
	}
}
