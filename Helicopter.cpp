//
// CS207 FINAL PROJECT: ANA, SOLOMON, KARLA
//

#include "Helicopter.h"
void Helicopter::initVariables(){
    this->pointCount = rand() % 2+1; //Randomized between 1-3
    this->speed   = static_cast<float>(this->pointCount); //will depend on pointCount
    this->hpMax   = static_cast<int>(this->pointCount);
    this->points  = this->pointCount;
}
void Helicopter::initTexture(){
    //Load a texture from file
    if(!this->texture.loadFromFile("../textures/helicopter.png"))
    {
        cout << "ERROR::HELICOPTER::INITTEXTURE::Could not load texture file" << "\n";
    }
}
void Helicopter::initSprite(){
    //Set texture to the sprite
    this->sprite.setTexture(this->texture);

    //Resize sprite
    this->sprite.scale(0.15f, 0.15f);
}

// Constructor Destructor
Helicopter::Helicopter(float pos_x, float pos_y){
    this -> initVariables();
    this -> initTexture();
    this -> initSprite();
    this -> sprite.setPosition(pos_x, pos_y);

}
Helicopter::~Helicopter(){}

//Accessors
const FloatRect Helicopter::getBounds() const{
    return this->sprite.getGlobalBounds();
}
const int& Helicopter::getPoints() const { //Return how many points each enemy gets
    return this->points;
}

//Functions
void Helicopter::update(){
    this->sprite.move(this->speed, 0.f );
}
void Helicopter::render(RenderTarget* target){
    target->draw(this->sprite);
}
