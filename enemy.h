#ifndef ENEMY_TYPES
#define ENEMY_TYPES
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
using namespace std;

class Enemy {
public:
    Enemy(float startX, float startY, float speed, int health, const vector<string>& textureFiles, float scaleX = 1.0f, float scaleY = 1.0f)
        : speed(speed), health(health), currentFrame(0), frameTime(0), frameDuration(0.2f) {
        for (const auto& file : textureFiles) {
            sf::Texture tempTexture;
            if (!tempTexture.loadFromFile(file)) {
                return;
            }
            textures.push_back(move(tempTexture));
        }
        sprite.setTexture(textures[0]);
        sprite.setPosition(startX, startY);
        sprite.setOrigin(textures[0].getSize().x / 2, textures[0].getSize().y / 2);
        sprite.setScale(scaleX, scaleY);
    }

    virtual ~Enemy() = default;

    virtual void update() {
        sprite.move(speed, 0);
        frameTime += clock.restart().asSeconds();
        if (frameTime >= frameDuration) {
            currentFrame = (currentFrame + 1) % textures.size();
            sprite.setTexture(textures[currentFrame]);
            frameTime = 0;
        }
    }

    virtual void draw(sf::RenderWindow& window)const {
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }

    float getRight() const {
        return sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
    }

    void takeDamage(int damage) {
        health -= damage;
    }

    bool isDead() const {
        return health <= 0;
    }

protected:
    sf::Sprite sprite;
    vector<sf::Texture> textures;
    float speed;
    int health;
    size_t currentFrame;
    sf::Clock clock;
    float frameTime;
    const float frameDuration;
};

class Zombie : public Enemy {
public:
    Zombie(float startX, float startY) : Enemy(startX, startY, 0.09f, 1, { "sprites/zombie_sprites/zombie01.png", "sprites/zombie_sprites/zombie02.png", "sprites/zombie_sprites/zombie03.png", "sprites/zombie_sprites/zombie04.png" }, 0.6f, 0.6f) {}
};

class Vampire : public Enemy {
public:
    Vampire(float startX, float startY) : Enemy(startX, startY, 0.15f, 1, { "sprites/vampire_sprites/vampire01.png", "sprites/vampire_sprites/vampire02.png", "sprites/vampire_sprites/vampire03.png", "sprites/vampire_sprites/vampire04.png" }, 1.5f, 1.5f) {}
};

class Werewolf : public Enemy {
public:
    Werewolf(float startX, float startY) : Enemy(startX, startY, 0.11f, 6, { "sprites/werewolf_sprites/werewolf01.png", "sprites/werewolf_sprites/werewolf02.png", "sprites/werewolf_sprites/werewolf03.png", "sprites/werewolf_sprites/werewolf04.png" }, 2.0f, 2.0f) {}
};

class Slime : public Enemy {
public:
    Slime(float startX, float startY) : Enemy(startX, startY, 0.125f, 3, { "sprites/slime_sprites/slime01.png", "sprites/slime_sprites/slime02.png", "sprites/slime_sprites/slime03.png", "sprites/slime_sprites/slime04.png" }, 1.0f, 1.0f) {}
};

class Pegote : public Enemy {
public:
    Pegote(float startX, float startY) : Enemy(startX, startY, 0.105f, 2, { "sprites/pegote_sprites/pegote01.png", "sprites/pegote_sprites/pegote02.png", "sprites/pegote_sprites/pegote03.png", "sprites/pegote_sprites/pegote04.png" }, 1.0f, 1.0f) {}
};
#endif