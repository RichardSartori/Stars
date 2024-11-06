#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "configuration.hpp"
#include "random.hpp"
#include "star.hpp"

Star::Star(sf::Vector2f _position, float _depth)
	: position(_position), depth(_depth)
{}

Star Star::from_random(void) {
	// we don't want stars to dissapear on screen
	// -> avoid creating stars with end position on screen
	static sf::Rect<float> const screen = {
		-conf::window::CENTER_F * conf::stars::NEAR,
		conf::window::SIZE_F * conf::stars::NEAR
	};

	std::size_t fails = 0;

	while (true) {
		float x = Random::getFloat(conf::window::SIZE_F.x);
		float y = Random::getFloat(conf::window::SIZE_F.y);
		float z = Random::getFloat(conf::stars::NEAR, conf::stars::FAR);
		sf::Vector2f position{ x, y };
		// position is around conf::window::CENTER_F, shift to around (0,0)
		position -= conf::window::CENTER_F;
		// fill the entire far plane
		position *= conf::stars::FAR;
		// skip stars that dissapear on screen
		if (!screen.contains(position)) return Star{ position, z };
		++fails;
		if (fails < conf::stars::MAX_GEN_FAILS) continue;
		std::cerr << "too many failed attempts at creating stars\n";
		std::exit(EXIT_FAILURE);
	}
}

void Star::update_geometry(sf::VertexArray& va, std::size_t index) const {

	float scale = 1.0f / this->depth;
	sf::Vector2f position = conf::window::CENTER_F + this->position * scale;
	float radius = conf::stars::RADIUS * scale;

	va[index + 0].position = { position.x - radius, position.y - radius };
	va[index + 1].position = { position.x + radius, position.y - radius };
	va[index + 2].position = { position.x + radius, position.y + radius };
	va[index + 3].position = { position.x - radius, position.y + radius };

	float depth_ratio = this->depth - conf::stars::NEAR;
	depth_ratio /= conf::stars::FAR - conf::stars::NEAR;
	float color_ratio = (1.0f - depth_ratio) * 255.0f;
	uint8_t shade = static_cast<uint8_t>(color_ratio);
	sf::Color color{ shade, shade, shade };

	va[index + 0].color = color;
	va[index + 1].color = color;
	va[index + 2].color = color;
	va[index + 3].color = color;
}

void Star::set_texture(sf::Texture& texture, sf::VertexArray& va) {
	texture.loadFromFile(conf::stars::TEXTURE_PATH);
	texture.setSmooth(true);
	texture.generateMipmap();
	sf::Vector2f const tex_size = static_cast<sf::Vector2f>(texture.getSize());

	for (std::size_t index = 0; index < conf::stars::COUNT; ++index) {
		va[4 * index + 0].texCoords = {       0.0f,       0.0f };
		va[4 * index + 1].texCoords = { tex_size.x,       0.0f };
		va[4 * index + 2].texCoords = { tex_size.x, tex_size.y };
		va[4 * index + 3].texCoords = {       0.0f, tex_size.y };
	}
}
