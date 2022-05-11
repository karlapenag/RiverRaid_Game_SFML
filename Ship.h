//
// CS207 FINAL PROJECT: ANA, SOLOMON, KARLA
//

#ifndef SFML_APP_SHIP_H
#define SFML_APP_SHIP_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>

using namespace std;
using namespace sf;

class Ship {
private:
    Sprite sprite;
    Texture texture;
    int pointCount;
    int points;

    //Private functions
    void initVariables();
    void initTexture();
    void initSprite();

public:
    Ship(float pos_x, float pos_y);
    virtual ~Ship();

    //Accessors
    const FloatRect getBounds() const;
    const int& getPoints() const; //Return how many points each enemy gets

    //Functions
    void update(float speed);
    void render(RenderTarget* target);
};



#endif //SFML_APP_SHIP_H
