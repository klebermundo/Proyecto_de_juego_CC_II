#ifndef VIDA_H
#define VIDA_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
using namespace std;

class Health {
public:
    Health(int initialHealth, const sf::Font& font, const sf::Texture& heartTexture, float heartScale)
        : health(initialHealth) 
    {
        heart.setTexture(heartTexture);
        heart.setScale(heartScale, heartScale);
        heart.setPosition(10, 10);

        healthText.setFont(font);
        healthText.setCharacterSize(36);
        healthText.setFillColor(sf::Color::White);
        updateText();
    }

    void decrease() {
        health--;
        updateText();
    }

    int getHealth() const {
        return health;
    }

    void draw(sf::RenderWindow& window) const{
        window.draw(heart);
        window.draw(healthText);
    }

private:
    int health;
    sf::Sprite heart;
    sf::Text healthText;

    void updateText() {
        healthText.setString(to_string(health));
        healthText.setPosition(heart.getPosition().x + heart.getGlobalBounds().width + 10, heart.getPosition().y);
    }
};
#endif
