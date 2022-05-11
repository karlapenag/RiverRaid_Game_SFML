//
// CS207 FINAL PROJECT: ANA, SOLOMON, KARLA
//

#ifndef SFML_APP_BULLET_H
#define SFML_APP_BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>

using namespace std;
using namespace sf;

class Bullet {
private:
    Sprite shape;

    //Direction of bullets
    Vector2f direction;
    float movementSpeed;

public:
    Bullet();
    Bullet(Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
    virtual ~Bullet();

    //Accessor
    FloatRect getBounds() const;

    void update();
    void render(RenderTarget* target);
};


#endif //SFML_APP_BULLET_H
