//
// CS207 FINAL PROJECT: ANA, SOLOMON, KARLA
//

#ifndef SFML_APP_GAME_H
#define SFML_APP_GAME_H
#include<map>

#include "player.h"
#include "Bullet.h"
#include "Helicopter.h"
#include "Ship.h"
#include "Fuel.h"
#include "mapShape.h"
#include<sstream>
#include<string>

/*
 * Class that acts as the game engine.
 * Wrapper class.
 */

class Game {
private:
    //Window
    VideoMode videoMode;
    RenderWindow* window; //Window is pointer because we want to close it (dyn allocate)
    Event ev;

    //Resources
    map<string, Texture*> textures; //For each string there is a texture
    vector<Bullet*> bullet;

    //GUI
    Font font;
    Text pointText;
    Text lifeText;
    Text fuelText;
    Text gameOverText;

    //World Background
    TileMap map;
    int** mapArray;

    //Systems
    unsigned points;
    unsigned lives;

    //Player
    player* Player;

    //PlayerGUI
    RectangleShape playerHpBar; //current value
    RectangleShape playerHpBarBack; //max value

    //Enemies
    float spawnTimer;
    float spawnTimerMax;
    float spawnTimerShips;
    float spawnTimerMaxShips;
    vector<Helicopter*> helicopters;
    vector<Ship*> ships;

    //Fuel
    vector<Fuel*> fuels;

    //Private functions
    void initWindow();
    void initWorld();
    void initTextures();
    void initGUI();
    void initSystems();
    void initPlayer();
    void initHelicopter();
    void initShip();
    void initFuel();

public:
    float speed;
    //Constructors and Destructors
    Game();
    ~Game();

    //Functions
    void run();

    void updatepollEvents();
    void updateWorld();
    void updateInput();
    void updateGUI();
    void updateCollision();
    void updateBullets();
    void updateHelicopters();
    void updateShips();
    void updateFuels();
    void updateCombat();
    void update();

    void renderGUI();
    void renderWorld();
    void render();

};


#endif //SFML_APP_GAME_H