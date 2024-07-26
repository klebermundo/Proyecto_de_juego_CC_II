#ifndef PHASE
#define PHASE

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
#include "Enemy_factory.h"
using namespace std;

class GameState {
public:
    virtual ~GameState() = default;
    virtual void advancePhase(int& phase, int& enemiesKilled, sf::Clock& gameClock, sf::Music& backgroundMusic) = 0;
    virtual int getEnemyType() = 0;
};

class Phase1 : public GameState {
public:
    void advancePhase(int& phase, int& enemiesKilled, sf::Clock& gameClock, sf::Music& backgroundMusic) override {
        if (enemiesKilled >= 40 || gameClock.getElapsedTime().asSeconds() >= 60) {
            phase = 1;
            enemiesKilled = 0;
            gameClock.restart();
        }
    }

    int getEnemyType() override {
        return rand() % 1; // Solo zombies
    }
};

class Phase2 : public GameState {
public:
    void advancePhase(int& phase, int& enemiesKilled, sf::Clock& gameClock, sf::Music& backgroundMusic) override {
        if (enemiesKilled >= 50 || gameClock.getElapsedTime().asSeconds() >= 60) {
            phase = 2;
            backgroundMusic.stop();
            if (!backgroundMusic.openFromFile("sonidos\\Jhon_Camara-Battle(Solarmax 2).mp3")) {
                return;
            }
            backgroundMusic.play();
            enemiesKilled = 0;
            gameClock.restart();
        }
    }

    int getEnemyType() override {
        return rand() % 2; // Zombies y vampiros
    }
};

class Phase3 : public GameState {
public:
    void advancePhase(int& phase, int& enemiesKilled, sf::Clock& gameClock, sf::Music& backgroundMusic) override {
        if (enemiesKilled >= 40 || gameClock.getElapsedTime().asSeconds() >= 60) {
            phase = 3;
            enemiesKilled = 0;
            gameClock.restart();
        }
    }

    int getEnemyType() override {
        return rand() % 3; // Zombies, vampiros y werewolfs
    }
};

class Phase4 : public GameState {
public:
    void advancePhase(int& phase, int& enemiesKilled, sf::Clock& gameClock, sf::Music& backgroundMusic) override {
        if (enemiesKilled >= 55 || gameClock.getElapsedTime().asSeconds() >= 80) {
            phase = 4;
            backgroundMusic.stop();
            if (!backgroundMusic.openFromFile("sonidos\\Bjorn_Lynne-Gateway_of_the_Gods.mp3")) {
                return;
            }
            backgroundMusic.play();
            enemiesKilled = 0;
            gameClock.restart();
        }
    }

    int getEnemyType() override {
        return rand() % 4; // Zombies, vampiros, werewolfs y slimes
    }
};

class Phase5 : public GameState {
public:
    void advancePhase(int& phase, int& enemiesKilled, sf::Clock& gameClock, sf::Music& backgroundMusic) override {
        if (enemiesKilled >= 20 || gameClock.getElapsedTime().asSeconds() >= 80) {
            phase = 5;
            enemiesKilled = 0;
            gameClock.restart();
        }
    }

    int getEnemyType() override {
        return rand() % 5; // Zombies, vampiros, werewolfs, slimes y pegotes
    }
};

class Phase6 : public GameState {
public:
    void advancePhase(int& phase, int& enemiesKilled, sf::Clock& gameClock, sf::Music& backgroundMusic) override {
        // No hay fase siguiente
        if (enemiesKilled >= 70 || gameClock.getElapsedTime().asSeconds() >= 200) {
            // Detener la generación de enemigos
        }
    }

    int getEnemyType() override {
        return -1; // No generar enemigos
    }
};

#endif
