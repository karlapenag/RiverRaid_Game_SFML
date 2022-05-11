//
// CS207 FINAL PROJECT: ANA, SOLOMON, KARLA
//

#ifndef SFML_APP_HELICOPTER_H
#define SFML_APP_HELICOPTER_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>

using namespace std;
using namespace sf;


class Helicopter {
private:
    Sprite sprite;
    Texture texture;
    int pointCount;
    float speed;
    int hpMax;
    int points;

    //Private functions
    void initVariables();
    void initTexture();
    void initSprite();

public:
    Helicopter(float pos_x, float pos_y);
    virtual ~Helicopter();

    //Accessors
    const FloatRect getBounds() const;
    const int& getPoints() const; //Return how many points each enemy gets

    //Functions
    void update();
    void render(RenderTarget* target);
};


#endif //SFML_APP_HELICOPTER_H
