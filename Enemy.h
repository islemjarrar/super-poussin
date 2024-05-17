#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <random>

class Enemy {
public:
    sf::Sprite sprite;
    float enemySpeed;

    Enemy(const sf::Texture& texture);
    void Update(float deltaTime);
    bool IsOffScreen(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

#endif // ENEMY_H

