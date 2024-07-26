#ifndef BOSS
#define BOSS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
using namespace std;
class FinalBoss {
public:
static FinalBoss* getInstance(float startX = 0, float startY = 0, float speed = 0, int health = 0, int shield = 0) {
    static FinalBoss instance(startX, startY, speed, health, shield);
    return &instance;
}

    FinalBoss(const FinalBoss&) = delete;
    FinalBoss& operator=(const FinalBoss&) = delete;

    void update() {
        float elapsed = clock.restart().asSeconds();
        frameTime += elapsed;

        if (frameTime >= frameDuration) {
            currentFrame = (currentFrame + 1) % (currentShield > 0 ? movementTextures.size() : idleTextures.size());
            sprite.setTexture(currentShield > 0 ? movementTextures[currentFrame] : idleTextures[currentFrame % idleTextures.size()]);
            sprite.setScale(scale, scale);
            frameTime = 0;
        }

        if (currentShield <= 0) {
            speed = 0; // Inmovilizar jefe final
            shieldTimer -= elapsed;
            if (shieldTimer <= 0) {
                currentShield = maxShield;
                speed = originalSpeed;
                shieldTimer = shieldRegenTime;
            }
        }
        else {
            sprite.move(speed, 0);
        }
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(sprite);
    }

    void takeDamage(int damage) {
        if (currentShield > 0) {
            currentShield -= damage;
        }
        else {
            health -= damage;
        }
    }

    bool isDead() const {
        return health <= 0;
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }

    float getRight() const {
        return sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
    }

private:
    FinalBoss(float startX, float startY, float speed, int health, int shield)
        : speed(speed), health(health), maxShield(shield), currentShield(shield),
          shieldRegenTime(7), shieldTimer(shieldRegenTime), currentFrame(0), frameTime(0), frameDuration(0.3f), scale(4.0f)
    {
        vector<string> movementFiles = { "sprites/boss_sprites/boss01.png", "sprites/boss_sprites/boss02.png", "sprites/boss_sprites/boss03.png", "sprites/boss_sprites/boss04.png" };
        for (const auto& file : movementFiles) {
            sf::Texture tempTexture;
            if (!tempTexture.loadFromFile(file)) {
                return;
            }
            movementTextures.push_back(move(tempTexture));
        }

        vector<string> idleFiles = { "sprites/boss_sprites/boss011.png", "sprites/boss_sprites/boss022.png", "sprites/boss_sprites/boss033.png", "sprites/boss_sprites/boss044.png" };
        for (const auto& file : idleFiles) {
            sf::Texture tempTexture;
            if (!tempTexture.loadFromFile(file)) {
                return;
            }
            idleTextures.push_back(move(tempTexture));
        }

        sprite.setTexture(movementTextures[0]);
        sprite.setPosition(startX, startY);
        sprite.setOrigin(movementTextures[0].getSize().x / 2, movementTextures[0].getSize().y / 2);
        sprite.setScale(scale, scale);
    }

    sf::Sprite sprite;
    vector<sf::Texture> movementTextures;
    vector<sf::Texture> idleTextures;
    float speed;
    const float originalSpeed = 0.09f;
    int health;
    const int maxShield;
    int currentShield;
    const float shieldRegenTime;
    float shieldTimer;
    sf::Clock clock;
    size_t currentFrame;
    float frameTime;
    const float frameDuration;
    const float scale;
};

#endif