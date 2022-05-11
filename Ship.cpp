//
// CS207 FINAL PROJECT: ANA, SOLOMON, KARLA
//

#include "Ship.h"

void Ship::initVariables(){
    this->pointCount = rand() % 8 + 3; //Randomized between 0 to 8 get 3-10
    this->points  = this->pointCount;
}
void Ship::initTexture(){
    //Load a texture from file
    if(!this->texture.loadFromFile("../textures/boat.png"))
    {
        cout << "ERROR::SHIP::INITTEXTURE::Could not load texture file" << "\n";
    }
}
void Ship::initSprite(){
    //Set texture to the sprite
    this->sprite.setTexture(this->texture);

    //Resize sprite
    this->sprite.scale(0.3f, 0.3f);
}

Ship::Ship(float pos_x, float pos_y){
    this -> initVariables();
    this -> initTexture();
    this -> initSprite();
    this -> sprite.setPosition(pos_x, pos_y);

}
Ship::~Ship(){}

//Accessors
const FloatRect Ship::getBounds() const{
    return this->sprite.getGlobalBounds();
}
const int& Ship::getPoints() const { //Return how many points each enemy gets
    return this->points;
}

//Functions
void Ship::update(float speed){
    this->sprite.move(0.f, speed);
}
void Ship::render(RenderTarget* target){
    target->draw(this->sprite);
}
