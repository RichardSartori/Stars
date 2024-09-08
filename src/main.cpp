#include <algorithm>
#include <vector>

#include <SFML/Graphics.hpp>

#include "events.hpp"
#include "configuration.hpp"
#include "star.hpp"

std::vector<Star> create_stars(std::size_t count) {
	std::vector<Star> stars;
	stars.reserve(count);
	for (std::size_t _ = 0; _ < count; ++_) {
		stars.push_back(Star::from_random());
	}
	// sort from furthest to closest
	std::sort(stars.begin(), stars.end(), [](Star const& a, Star const& b) {
		return a.depth > b.depth;
	});
	return stars;
}

int main(void) {

	sf::RenderWindow window = sf::RenderWindow{
		conf::window::MODE,
		conf::window::NAME,
		sf::Style::Fullscreen
	};
	window.setFramerateLimit(conf::time::MAX_FPS);
	window.setMouseCursorVisible(false);

	std::vector<Star> stars = create_stars(conf::stars::COUNT);
	sf::VertexArray va{ sf::PrimitiveType::Quads, 4 * conf::stars::COUNT };
	sf::Texture star_texture;
	Star::set_texture(star_texture, va);
	sf::RenderStates states;
	states.texture = &star_texture;

	std::size_t index, furthest = 0;
	while (window.isOpen()) {
		processEvents(window);

		for (std::size_t i = 0; i < conf::stars::COUNT; ++i) {
			// order stays furthest to closest, with wrap around
			// process in reverse order = last star modified is furthest
			index = conf::stars::COUNT - i - 1;
			Star& star = stars[index];
			star.depth -= conf::stars::SPEED * conf::time::DELTA;
			if (star.depth < conf::stars::NEAR) {
				star.depth += conf::stars::FAR - conf::stars::NEAR;
				furthest = index;
			}
		}

		window.clear();

		// draw from furthest to closest
		for (std::size_t i = 0; i < conf::stars::COUNT; ++i) {
			index = (furthest + i) % conf::stars::COUNT;
			Star const& star = stars[index];
			// update VertexArray in natural ordering
			star.update_geometry(va, 4 * i);
		}

		window.draw(va, states);
		window.display();
	}

	return 0;
}
