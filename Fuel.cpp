//
// CS207 FINAL PROJECT: ANA, SOLOMON, KARLA
//

#include "Fuel.h"
//Private Functions

void Fuel::initTexture(){
    //Load a texture from file
    if(!this->texture.loadFromFile("../textures/fuel.png"))
    {
        cout << "ERROR::FUEL::INITTEXTURE::Could not load texture file" << "\n";
    }
}
void Fuel::initSprite(){
    //Set texture to the sprite
    this->sprite.setTexture(this->texture);

    //Resize sprite
    this->sprite.scale(0.3f, 0.3f);
}

//Constructor Destructor
Fuel::Fuel(float pos_x, float pos_y){
    this -> initTexture();
    this -> initSprite();
    this->sprite.setPosition(pos_x, pos_y);
}
Fuel::~Fuel(){}

//Accessors
const FloatRect Fuel::getBounds() const{
    return this -> sprite.getGlobalBounds();
}

//Functions
void Fuel::update(float speed){
    //Update player GUI. PlayerHPBar (only the front one)
    //Loose HP
    this->sprite.move(0.f, speed);


}
void Fuel::render(RenderTarget *target){
    target->draw(this->sprite);
}

