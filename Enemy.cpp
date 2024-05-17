#include "Enemy.h"

Enemy::Enemy(const sf::Texture& texture) : sprite(texture), enemySpeed(50.0f) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xPosDist(0, 800 - int(sprite.getTextureRect().width));
    sprite.setPosition(xPosDist(gen), 0.0f);
}

void Enemy::Update(float deltaTime) {
    sprite.move(0.0f, enemySpeed * deltaTime);
}

bool Enemy::IsOffScreen(const sf::RenderWindow& window) {
    return sprite.getPosition().y > window.getSize().y;
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

