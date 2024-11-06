#pragma once

#include <cstdint>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace conf {

	namespace window {
		static constexpr char const* NAME = "Stars";
		static sf::VideoMode const MODE = { 2560, 1440, 24 };
		static sf::Vector2u const SIZE = { MODE.width, MODE.height };
		static sf::Vector2f const SIZE_F = static_cast<sf::Vector2f>(SIZE);
		static sf::Vector2f const CENTER_F = SIZE_F / 2.0f;
	}

	namespace time {
		static constexpr uint32_t MAX_FPS = 144;
		static constexpr float DELTA = 1.0f / static_cast<float>(MAX_FPS);
	}

	namespace stars {
		static constexpr std::size_t COUNT = 100000;
		static constexpr float RADIUS = 40.0f;
		static constexpr float FAR = 10.0f;
		static constexpr float NEAR = 0.1f;
		static constexpr float SPEED = 1.0f;
		static constexpr std::size_t MAX_GEN_FAILS = 10;
		static constexpr char const* TEXTURE_PATH = "textures/star.png";
	}
}
