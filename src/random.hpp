#pragma once

#include <random>

class Random {
public:

	static float getFloat(float max);
	static float getFloat(float min, float max);

private:
	// members
	std::mt19937 gen;

	// methods
	static Random& get(void);
	Random(void);
};
