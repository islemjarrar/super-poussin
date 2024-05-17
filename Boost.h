#ifndef BOOST_H
#define BOOST_H

#include <SFML/Graphics.hpp>

class Boost {
public:
    sf::Sprite sprite;
    float duration;

    Boost(const sf::Texture& texture);
    void draw(sf::RenderWindow& window) const;
};

#endif // BOOST_H


