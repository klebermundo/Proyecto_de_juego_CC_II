#ifndef AIM
#define AIM
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
struct AimCursor {
    sf::Sprite sprite;
    sf::Texture texture;

    AimCursor() {
        if (!texture.loadFromFile("sprites/miras_sprites/mira_francotirador2.png")) {
            return;
        }
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    }
    void updatePosition(const sf::RenderWindow& window) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sprite.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    }
    void setSize(float width, float height) {
        sf::Vector2u textureSize = texture.getSize();
        sprite.setScale(width / textureSize.x, height / textureSize.y);
    }
    void draw(sf::RenderWindow& window) const {
        window.draw(sprite);
    }
};
#endif