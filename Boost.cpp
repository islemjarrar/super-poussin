#include "Boost.h"

Boost::Boost(const sf::Texture& texture) : sprite(texture), duration(5.0f) {
    sprite.setPosition(rand() % 800, 450);  // Random x position at y = 450
}

void Boost::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

