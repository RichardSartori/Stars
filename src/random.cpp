#include "random.hpp"

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

Random::Random(void) {
#ifdef STAR_DEBUG
	std::size_t SEED = 42;
	this->gen = std::mt19937(SEED);
#else // STAR_DEBUG
	std::random_device rd;
	this->gen = std::mt19937(rd());
#endif // STAR_DEBUG
}
