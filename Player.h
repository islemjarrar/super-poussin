#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"

class Player {
public:
    sf::Sprite sprite;
    std::vector<sf::IntRect> walkFrames;
    sf::IntRect idleRect;
    const sf::IntRect* currentAnimation;
    sf::Clock animationClock;
    int currentFrame;
    float speed;
    float boostSpeed;
    bool isBoosted;
    sf::Clock boostClock;
    float boostDuration;

    Player(const sf::Texture& texture);
    void Update(float deltaTime, const sf::Vector2f& windowSize);
    void UpdateAnimation(float deltaTime);
    void Shoot(std::vector<Bullet>& bullets, const sf::Texture& bulletTexture);
    void draw(sf::RenderWindow& window);
    void ApplyBoost();

private:
    sf::Vector2f frameSize;
};

#endif // PLAYER_H


