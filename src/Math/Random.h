#pragma once
#include <random>

class Randomness {
public:
	static std::mt19937& Generator() {
		static std::mt19937 gen{ std::random_device{}() };
		return gen;
	}

	static int Range(int min, int max) {
		std::uniform_int_distribution<int> dist(min, max);
		return dist(Generator());
	}

	static float Range(float min, float max) {
		std::uniform_real_distribution<float> dist(min, max);
		return dist(Generator());
	}
};