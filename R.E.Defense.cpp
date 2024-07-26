#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
using namespace std;

// Clase base para los enemigos
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

// Clases derivadas para cada tipo de enemigo
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

// Clase base para el estado del juego
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

// Fábrica de enemigos utilizando el patrón Factory Method
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

// Clase de vida
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


int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(1500, 700), "RESIDENT EVIL DEFENSE: THE LAST STAND");
    window.setMouseCursorVisible(false);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("sprites/fondos_sprites/fondo01.jpg")) {
        return -1;
    }
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        float(window.getSize().x) / backgroundTexture.getSize().x,
        float(window.getSize().y) / backgroundTexture.getSize().y
    );

    sf::Texture heartTexture;
    heartTexture.loadFromFile("sprites\\corazones_sprites\\corazon01.png");
    sf::Font font;
    font.loadFromFile("Poppins\\Poppins-Regular.ttf");

    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("sonidos\\Glorious_Morning.mp3")) {
        return -1;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    sf::SoundBuffer clickSoundBuffer;
    if (!clickSoundBuffer.loadFromFile("sonidos\\pistol_sound.mp3")) {
        return -1; // Manejo de error si el archivo de sonido no se carga
    }
    sf::Sound clickSound;
    clickSound.setBuffer(clickSoundBuffer);
    sf::Texture gameOverTexture;
    if (!gameOverTexture.loadFromFile("sprites\\ventanas_sprites\\ventanaGameOver.png")) {
        return -1; // Manejo de error si el archivo de imagen no se carga
    }
    sf::Sprite gameOverSprite;
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(window.getSize().x / 2 - gameOverTexture.getSize().x / 2,
                               window.getSize().y / 2 - gameOverTexture.getSize().y / 2);

    bool gameOver = false;
    EnemyFactory::init();
    vector<unique_ptr<Enemy>> enemies;
    sf::Time enemySpawnTime = sf::seconds(0.8f);
    Health health(20, font, heartTexture, 0.5f);
    unique_ptr<FinalBoss> finalBoss = nullptr;
    sf::Clock enemySpawnClock;

    int phase = 0;
    int enemiesKilled = 0;
    bool bossDefeated = false;
    bool bossSpawned = false;
    sf::Clock spawnClock;
    sf::Clock gameClock;
    sf::Clock enemyClock;

    AimCursor aimCursor;
    aimCursor.setSize(150.0f, 150.0f); // Ajusta el tamaño del cursor según sea necesario

    while (window.isOpen()) {
        // Manejar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f clickPosition(event.mouseButton.x, event.mouseButton.y);
                clickSound.play();
                // Verificar si algún enemigo fue clickeado
                for (auto& enemy : enemies) {
                    if (enemy->getBounds().contains(clickPosition)) {
                        enemy->takeDamage(1);
                        if (enemy->isDead()) {
                            if (dynamic_cast<Slime*>(enemy.get())) {
                                float x = enemy->getBounds().left;
                                float y = enemy->getBounds().top;
                                enemies.push_back(EnemyFactory::createPegote(x - 30, y,0)); // Pegote a la izquierda
                                enemies.push_back(EnemyFactory::createPegote(x + 30, y,0)); // Pegote a la derecha
                            }
                            enemiesKilled++;
                        }
                        break; // Salir del bucle después de aplicar el daño
                    }
                }

                // Verificar si el jefe final fue clickeado
                if (finalBoss && finalBoss->getBounds().contains(clickPosition)) {
                        finalBoss->takeDamage(1);
                    if (finalBoss->isDead()) {
                        gameOver = true;
                    }
                }
            }
        }

        // Generar enemigos
        if (enemySpawnClock.getElapsedTime() >= enemySpawnTime && phase < 5) {
            auto enemy = EnemyFactory::createRandomEnemy(phase);
            if (enemy) {
                enemies.push_back(std::move(enemy));
            }
            enemySpawnClock.restart();
        }

        // Actualizar enemigos
        for (auto& enemy : enemies) {
            enemy->update();
        }

        // Eliminar enemigos muertos
        enemies.erase(remove_if(enemies.begin(), enemies.end(),
            [](const unique_ptr<Enemy>& enemy) { return enemy->isDead(); }),
            enemies.end());

    // Avanzar la fase y crear el jefe final en la fase 5
        if (phase < 4) {
            EnemyFactory::phaseState[phase]->advancePhase(phase, enemiesKilled, gameClock, backgroundMusic);
        } else if (phase >= 4 && !bossSpawned) {
           finalBoss.reset(FinalBoss::getInstance(-236.0f, 200.0f, 0.09f, 100, 10)); // Crear y asignar la instancia del jefe final
            bossSpawned = true;
        }

        // Dibujar todo
        window.clear();
        // Dibujar el fondo primero
        window.draw(backgroundSprite);
        // Dibujar enemigos
        for (const auto& enemy : enemies) {
            enemy->draw(window);
        }
        // Dibujar el jefe final en la fase 5
        if (finalBoss) {
            finalBoss->update();
            finalBoss->draw(window);
        }

        // Dibujar la vida y el cursor de puntería
        health.draw(window);
        aimCursor.updatePosition(window);
        aimCursor.draw(window);

        // Verificar si algún enemigo ha cruzado la pantalla
        for (auto it = enemies.begin(); it != enemies.end(); ) {
            if ((*it)->getRight() > window.getSize().x) {
                health.decrease();
                it = enemies.erase(it);
            }
            else {
                ++it;
            }
        }

        // Verificar si el jefe final ha cruzado la pantalla
        if (finalBoss && finalBoss->getRight() > window.getSize().x) {
            gameOver=true;
        }
        if (gameOver) {
            window.draw(gameOverSprite);
            window.display();
            sf::sleep(sf::seconds(3)); // Pausar por 3 segundos antes de cerrar la ventana
            window.close();
            finalBoss.reset();
        } else {
            window.display();
        }
    }

    return 0;
}