#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Boost.h"
#include<SFML/Audio.hpp>
#include<sstream>
void displayStartMenu(sf::RenderWindow& window) {
    // Load font
    sf::Font font;
    if (!font.loadFromFile("font/bubbly.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    // Title Text
    sf::Text title;
    title.setFont(font);
    title.setString("Super Poussin");
    title.setCharacterSize(70);
    title.setFillColor(sf::Color::White);
    title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 200);

    // Start Text
    sf::Text startText;
    startText.setFont(font);
    startText.setString("Appuyez sur ENTREE ");
    startText.setCharacterSize(45);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(800 / 2 - startText.getGlobalBounds().width / 2, 400);

    // Background Texture and Sprite
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("image/bg.jpg")) {
        std::cerr << "Failed to load background texture!" << std::endl;
        return;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                return; // Exit the start menu and start the game
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(title);
        window.draw(startText);
        window.display();
    }
}


int main() {
    bool gamePaused = false;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sup");
    window.setFramerateLimit(60);
    displayStartMenu(window);
    // Audio
 // BackgroundAudio Buffer
    sf::SoundBuffer backgroundAudioBuffer;
    backgroundAudioBuffer.loadFromFile("audio/audio1.wav");
    // Chargement du background audio
    sf::Sound backgroundAudio;
    backgroundAudio.setBuffer(backgroundAudioBuffer);
    //gameOverSound Buffer
    sf::SoundBuffer gameOverSoundBuffer;
    gameOverSoundBuffer.loadFromFile("audio/over.wav");
    // Chargement du game over sound
    sf::Sound gameOverSound;
    gameOverSound.setBuffer(gameOverSoundBuffer);
    // Lecture du background audio
    backgroundAudio.setLoop(true);
    backgroundAudio.play();

    // Load textures
    sf::Texture playerTexture, enemyTexture, bulletTexture, backgroundTexture, boostTexture;
    if (!playerTexture.loadFromFile("image/playerWalk.png") ||
        !enemyTexture.loadFromFile("image/bomb.png") ||
        !bulletTexture.loadFromFile("image/bullet.png") ||
        !backgroundTexture.loadFromFile("image/bg.jpg") ||
        !boostTexture.loadFromFile("image/boost.png")) {
        std::cerr << "Failed to load textures!" << std::endl;
        return -1;
    }

    sf::Sprite backgroundSprite(backgroundTexture);
    // Game Over Texture et Sprite
    sf::Texture gameOverTexture;
    gameOverTexture.loadFromFile("image/gameover.png");
    sf::Sprite gameOverSprite;
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(800 / 2 - gameOverSprite.getGlobalBounds().width / 2, 600 / 2 - gameOverSprite.getGlobalBounds().height / 2);

    // Create player
    Player player(playerTexture);

    // Enemy, Bullet, and Boost vectors
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    std::vector<Boost> boosts;

    // Score variables
    int score = 0;
    sf::Font font;
    if (!font.loadFromFile("font/bubbly.ttf")) {  // Make sure the font file is in your project directory
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24); // in pixels
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10.f, 10.f); // position on the screen

    float spawnTimer = 0.0f, spawnInterval = 2.0f, shootCooldown = 0.2f, timeSinceLastShot = 0.0f;
    float boostSpawnTimer = 0.0f, boostSpawnInterval = 10.0f; // Boost spawns every 10 seconds
    sf::Clock gameClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = gameClock.restart().asSeconds();
        if (timeSinceLastShot < shootCooldown) {
            timeSinceLastShot += deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeSinceLastShot >= shootCooldown) {
            player.Shoot(bullets, bulletTexture);
            timeSinceLastShot = 0.0f;
        }

        player.Update(deltaTime, sf::Vector2f(window.getSize()));

        spawnTimer += deltaTime;
        if (spawnTimer >= spawnInterval) {
            enemies.emplace_back(enemyTexture);
            spawnTimer = 0.0f;
        }

        boostSpawnTimer += deltaTime;
        if (boostSpawnTimer >= boostSpawnInterval) {
            boosts.emplace_back(boostTexture);
            boostSpawnTimer = 0.0f;
        }

        for (auto& enemy : enemies) {
            enemy.Update(deltaTime);
            if (enemy.IsOffScreen(window)) {
                enemy = enemies.back();
                enemies.pop_back();
            }
        }

        for (int i = bullets.size() - 1; i >= 0; --i) {
            bullets[i].Update(deltaTime);
            if (bullets[i].IsOffScreen(window)) {
                bullets.erase(bullets.begin() + i);
            }
        }

        for (int i = 0; i < bullets.size(); ++i) {
            for (int j = 0; j < enemies.size(); ++j) {
                if (bullets[i].sprite.getGlobalBounds().intersects(enemies[j].sprite.getGlobalBounds())) {
                    bullets.erase(bullets.begin() + i--);
                    enemies.erase(enemies.begin() + j--);
                    score += 10;  // Increase score
                    scoreText.setString("Score: " + std::to_string(score)); // Update score text
                    break;
                }
            }
        }

        for (auto it = boosts.begin(); it != boosts.end(); ) {
            if (player.sprite.getGlobalBounds().intersects(it->sprite.getGlobalBounds())) {
                player.ApplyBoost();
                it = boosts.erase(it);  // Remove the boost after collection
            }
            else {
                ++it;
            }
        }
        // Vérification de collision joueur-ennemi (bombe)
        for (const auto& enemy : enemies) {
            if (player.sprite.getGlobalBounds().intersects(enemy.sprite.getGlobalBounds())) {
                gamePaused = true;
                // Collision détectée
                backgroundAudio.stop(); // Arrêter la musique de fond
                gameOverSound.play();   // Jouer le son de fin de jeu
            }
        }
        window.clear();
        window.draw(backgroundSprite);
        if (gamePaused == false)
        {
            for (const auto& enemy : enemies) {
                window.draw(enemy.sprite);
            }
            for (const auto& bullet : bullets) {
                window.draw(bullet.sprite);
            }
            for (const auto& boost : boosts) {
                boost.draw(window);
            }
            player.draw(window);
        }
        else
        {
            window.draw(gameOverSprite);
        }


        window.draw(scoreText); // Draw the score
        window.display();
    }

    return 0;

}


