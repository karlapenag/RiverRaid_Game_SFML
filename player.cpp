//
// CS207 FINAL PROJECT: ANA, SOLOMON, KARLA
//

#include "player.h"

//Private functions
void player::initTexture(){
    //Load a texture from file
    if(!this->texture.loadFromFile("../textures/airplane.png"))
    {
        cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file" << "\n";
    }
}
void player::initSprite(){
    //Set texture to the sprite
    this->sprite.setTexture(this->texture);

    //Resize sprite
    this->sprite.scale(0.15f, 0.15f);
}
void player::initVariables(){
    this -> movementSpeed = 4.f;
    this -> attackCooldownMax = 10.f;
    this -> attackCooldown = this -> attackCooldownMax;
    this -> hpMax = 300.f;
    this -> hp = hpMax;
}


//Constructors and destructors
player::player(){
    this -> initVariables();
    this -> initTexture();
    this -> initSprite();
}
player:: ~player(){}


//Accessors
const Vector2f& player::getPos() const{
    //Get position from player to be able to create bullets coming out of player
    return this->sprite.getPosition();
}
const FloatRect player::getBounds() const{
    return this -> sprite.getGlobalBounds();
}
const int& player::getHp() const{
    return this->hp;
}
const int& player::getHpMax() const{
    return this->hpMax;
}


//Modifiers
void player::setPosition(const Vector2f pos){
    this->sprite.setPosition(pos);
}
void player::setPosition(const float x, const float y){
    this->sprite.setPosition(x,y);
}
void player::setHp(const int hp){
    //Set HBar equal to int we give
    this->hp = hp;
}

//Functions
void player::move(const float dirX, const float dirY){
    this->sprite.move(this -> movementSpeed * dirX, this -> movementSpeed * dirY);
}
const bool player::canAttack(){
    if (this->attackCooldown >= this->attackCooldownMax){
        this->attackCooldown += 0.5f;
        return true;
    }
    return false;
}
void player::updateAttack(){
    //Setting max to shoot bullets (so user can not just press
    // space and lots of bullets out, once it attacks it resets
    if(this->attackCooldown < this->attackCooldownMax){
        this->attackCooldown += 1.f;
    }
}
void player::update(){
    this->updateAttack();
}
void player::render(RenderTarget& target){
    target.draw(this->sprite);
}
