//
// CS207 FINAL PROJECT: ANA, SOLOMON, KARLA
//

#ifndef SFML_APP_FUEL_H
#define SFML_APP_FUEL_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>

using namespace std;
using namespace sf;

using namespace std;
using namespace sf;

class Fuel {
private:
    Sprite sprite;
    Texture texture;

//Private functions
    void initTexture();
    void initSprite();


public:
    Fuel(float pos_x, float pos_y);
    virtual ~Fuel();

    //Accessors
    const FloatRect getBounds() const;

    //Functions
    void update(float speed);
    void render(RenderTarget* target);

};



#endif //SFML_APP_FUEL_H
