#include "Bullet.h"

Bullet::Bullet(const sf::Texture& texture) : sprite(texture), bulletVelocity(500.0f) {}

void Bullet::Update(float deltaTime) {
    sprite.move(0.0f, -bulletVelocity * deltaTime);
}

bool Bullet::IsOffScreen(const sf::RenderWindow& window) {
    return sprite.getPosition().y < 0.0f;
}
