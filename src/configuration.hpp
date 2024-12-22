#pragma once

#include <cstdint>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace conf {

	namespace window {
		inline constexpr char const NAME[] = "Stars";
		inline constexpr unsigned int WIDTH = 2560;
		inline constexpr unsigned int HEIGHT = 1440;
		inline constexpr unsigned int BITS_PER_PIXEL = 24;
		inline sf::VideoMode const MODE = { WIDTH, HEIGHT, BITS_PER_PIXEL };
		inline sf::Vector2u const SIZE = { WIDTH, HEIGHT };
		inline sf::Vector2f const SIZE_F = static_cast<sf::Vector2f>(SIZE);
		inline sf::Vector2f const CENTER_F = SIZE_F / 2.0f;
	}

	namespace time {
		inline constexpr uint32_t MAX_FPS = 144;
		inline constexpr float DELTA = 1.0f / static_cast<float>(MAX_FPS);
	}

	namespace stars {
		inline constexpr std::size_t COUNT = 100000;
		inline constexpr float RADIUS = 40.0f;
		inline constexpr float FAR = 10.0f;
		inline constexpr float NEAR = 0.1f;
		inline constexpr float SPEED = 1.0f;
		inline constexpr std::size_t MAX_GEN_FAILS = 10;
		inline constexpr char const TEXTURE_PATH[] = "textures/star.png";
	}
}
