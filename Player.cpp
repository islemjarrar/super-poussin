#include "Player.h"

Player::Player(const sf::Texture& texture)
    : sprite(texture), currentAnimation(&idleRect), currentFrame(0), speed(150.0f),
    boostSpeed(300.0f), isBoosted(false), boostDuration(5.0f) {
    sprite.setPosition(sf::Vector2f(300.0f, 530.0f - 99.f + 17.f));
    frameSize = sf::Vector2f(85.f, 99.f);
    idleRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
    for (int i = 0; i < 8; i++) {
        walkFrames.push_back(sf::IntRect(frameSize.x * i, 0, frameSize.x, frameSize.y));
    }
    animationClock.restart();
}

void Player::Update(float deltaTime, const sf::Vector2f& windowSize) {
    float moveX = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        moveX -= isBoosted ? boostSpeed : speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        moveX += isBoosted ? boostSpeed : speed;
    }
    else {
        currentAnimation = &idleRect;
    }

    sprite.move(moveX * deltaTime, 0.0f);
    sprite.setPosition(
        std::max(0.0f, std::min(sprite.getPosition().x, windowSize.x - sprite.getTextureRect().width)),
        sprite.getPosition().y
    );

    UpdateAnimation(deltaTime);

    // Check if boost duration has ended
    if (isBoosted && boostClock.getElapsedTime().asSeconds() > boostDuration) {
        isBoosted = false;
    }
}

void Player::UpdateAnimation(float deltaTime) {
    float frameDuration = 0.3f;
    if (animationClock.getElapsedTime().asSeconds() > frameDuration) {
        currentFrame = (currentFrame + 1) % walkFrames.size();
        animationClock.restart();
        sprite.setTextureRect(walkFrames[currentFrame]);
    }
}

void Player::Shoot(std::vector<Bullet>& bullets, const sf::Texture& bulletTexture) {
    Bullet newBullet(bulletTexture);
    newBullet.sprite.setPosition(sprite.getPosition() + sf::Vector2f(sprite.getTextureRect().width / 2.0f, 0));
    bullets.push_back(newBullet);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::ApplyBoost() {
    isBoosted = true;
    boostClock.restart();
}

