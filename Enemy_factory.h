
#ifndef MONSTER_FACTORY
#define MONSTER_FACTORY

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
#include "enemy.h"
#include "Game_states.h"
using namespace std;
class EnemyFactory {
public:
    static unique_ptr<Enemy> createRandomEnemy(int phase) {
        int type = phaseState[phase]->getEnemyType();
        if (type == -1) {
            return nullptr; // No generar enemigos en la fase 6
        }
        int posY = rand() % 590 + 50;

        switch (type) {
            case 0: return make_unique<Zombie>(-50, posY);
            case 1: return make_unique<Vampire>(-50, posY);
            case 2: return make_unique<Werewolf>(-50, posY);
            case 3: return make_unique<Slime>(-50, posY);
            case 4: return make_unique<Pegote>(-50, posY);
            default: return make_unique<Zombie>(-50, posY); // Caso por defecto
        }
    }

    static unique_ptr<Pegote> createPegote(float x, float y, float offset) {
        return make_unique<Pegote>(x + offset, y);
    }

    static void init() {
        phaseState[0] = make_unique<Phase1>();
        phaseState[1] = make_unique<Phase2>();
        phaseState[2] = make_unique<Phase3>();
        phaseState[3] = make_unique<Phase4>();
        phaseState[4] = make_unique<Phase5>();
        phaseState[5] = make_unique<Phase6>();
    }

public: // Cambiado a public
    static unique_ptr<GameState> phaseState[6];
};

unique_ptr<GameState> EnemyFactory::phaseState[6];
#endif 
