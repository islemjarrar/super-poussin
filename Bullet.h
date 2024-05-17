#ifndef BULLET_H
#define BULLET_H

#include<SFML/Graphics.hpp>

class Bullet {
public:
	sf::Sprite sprite;
	float bulletVelocity;

	Bullet(const sf::Texture& texture);
	void Update(float deltaTime);
	bool IsOffScreen(const sf::RenderWindow&  window);
};

#endif // BULLET_H