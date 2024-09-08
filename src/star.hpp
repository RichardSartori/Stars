#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include "configuration.hpp"

struct Star {
	// members
	sf::Vector2f position;
	float depth;

	// methods
	Star(sf::Vector2f position, float depth);
	void update_geometry(sf::VertexArray& va, std::size_t index) const;

	// static functions
	static Star from_random(void);
	static void set_texture(sf::Texture&, sf::VertexArray&);
};
