//
// CS207 FINAL PROJECT: ANA, SOLOMON, KARLA
//

#include "Bullet.h"
//Constructors Destructor
Bullet::Bullet(){}
Bullet::Bullet(Texture *texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed){
    this->shape.setTexture(*texture);
    this->shape.setPosition(pos_x, pos_y);
    this->direction.x = dir_x;
    this->direction.y = dir_y;
    this->movementSpeed = movement_speed;
}
Bullet::~Bullet(){}

//Accessors
FloatRect Bullet::getBounds() const{
    return this->shape.getGlobalBounds();
}

//Functions
void Bullet::update(){
    //Movement
    this->shape.move(this->movementSpeed * this -> direction);
}
void Bullet::render(RenderTarget* target){
    target->draw(this->shape);
}