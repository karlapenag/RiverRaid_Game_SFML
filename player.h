//
// CS207 FINAL PROJECT: ANA, SOLOMON, KARLA
//

#ifndef SFML_APP_PLAYER_H
#define SFML_APP_PLAYER_H
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>

using namespace std;
using namespace sf;

class player {

private:
    Sprite sprite;
    Texture texture;
    float movementSpeed;

    float attackCooldown;
    float attackCooldownMax;

    int hp;
    int hpMax;

    //Private functions
    void initVariables();
    void initTexture();
    void initSprite();

public:
    player();
    virtual ~player();

    //Accessor
    const Vector2f& getPos() const;
    const FloatRect getBounds() const;
    const int& getHp() const;
    const int& getHpMax() const;

    //Modifiers
    //Set position overloaded functions
    void setPosition(const Vector2f pos);
    void setPosition(const float x, const float y);
    void setHp(const int hp);


    //Functions
    void move(const float dirX, const float dirY);
    const bool canAttack();
    void updateAttack();
    void update();
    void render(RenderTarget& target);

};


#endif //SFML_APP_PLAYER_H
