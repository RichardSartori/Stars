#include "random.hpp"

float Random::getFloat(void) {
	return Random::getFloat(1.0f);
}

float Random::getFloat(float max) {
	return Random::getFloat(0.0f, max);
}

float Random::getFloat(float min, float max) {
	Random& singleton = Random::get();
	std::uniform_real_distribution<float> dis(min, max);
	return dis(singleton.gen);
}

Random& Random::get(void) {
	static Random singleton{};
	return singleton;
}

Random::Random(void)
	: rd(), gen(rd())
{}
