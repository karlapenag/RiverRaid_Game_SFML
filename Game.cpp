//
// CS207 FINAL PROJECT: ANA, SOLOMON, KARLA
//

#include<fstream>
#include<math.h>
#include "Game.h"
int bulletTimer = 0;

//Private Functions
void Game::initWindow(){
    this -> videoMode.height = 640;
    this -> videoMode.width = 960;
    //this -> videoMode.getDesktopMode(); // desktop dimensions
    this -> window = new RenderWindow(this->videoMode ,"River Raid", Style::Close | Style::Titlebar);
    this -> window -> setFramerateLimit(144);
    this -> window ->setVerticalSyncEnabled(false);
}
void Game::initWorld() {
    string text;
    int number_of_tiles;
    number_of_tiles = 550 * 30; // 15990
    int mapShape[number_of_tiles]; //vertex array with map shape content

    //initial velocity
    this->speed=.7f;

    //upload text file with the map shape
    ifstream infile("river_raid_shape.txt");

    if (infile.fail()) {
        cout << "Input text file does not exist" << endl;
    } else {
        int counter=0;
        while (!infile.eof()) {
            getline(infile, text);
            for (auto x:text){
                if (isspace(x)!=0){
                    break;
                }
                else {
                    mapShape[counter]= x-'0'; // "-'0'" to use the numbers and not their ASCII values subtracting 48 (=0).
                    counter++;
                }
            }
        }
    }

    int mapWidth=30;
    int mapHeight=550;

    this->mapArray=new int*[mapHeight];
    int countTiles=0;

    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            this->mapArray[i] = new int[mapWidth];
        }
    }

    for (unsigned int i = mapHeight-1; i >= 0; i--) {
        if (i > 550){
            break;
        }
        for (unsigned int j = 0; j < mapWidth; ++j) {
            this->mapArray[i][j] = mapShape[countTiles];
            countTiles++;
            //cout << "mapX: " << i << " mapY: " << j << " = " << mapArray[i][j] << endl;
        }
    }

    if (!this->map.load("../textures/tileset.png", sf::Vector2u(32, 32), mapShape, mapWidth, mapHeight))
    {
        std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
    }

    //transform it (can see 20)

    this->map.setOrigin(0,16960);
}
void Game::initTextures(){
    this->textures["BULLET"] = new Texture();
    this->textures["BULLET"] ->loadFromFile("../textures/bullet.png");
}
void Game::initGUI(){
    //Load font
    if(!this->font.loadFromFile("../fonts/PixellettersFull.ttf"))
        cout << "ERROR::GAME::Failed to load font" <<"\n";

    //Init point text
    this->pointText.setFont(this->font); //Load font
    this->pointText.setCharacterSize(22);
    this->pointText.setFillColor(Color::White);
    //this->pointText.setString("test");
    this->lifeText.setPosition(Vector2f(0.f,0.f));


    //Init life text
    this->lifeText.setFont(this->font); //Load font
    this->lifeText.setCharacterSize(22);
    this->lifeText.setFillColor(Color::White);
    //this->lifeText.setString("test");
    this->lifeText.setPosition(Vector2f(0.f,22.f));

    //Init GameOVerText
    this->gameOverText.setFont(this->font); //Load font
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(Color::Red);
    this->gameOverText.setString("Game Over!");
    //Centering
    this->gameOverText.setPosition(this->window->getSize().x/2.f - this->gameOverText.getGlobalBounds().width/2.f,
                                   this->window->getSize().y/2.f - this->gameOverText.getGlobalBounds().height/2.f);


    //Init player GUI. Set size color and position of the rectangle healthbar shape
    this->playerHpBar.setSize(Vector2f(300.f, 25.f)); //Size
    this->playerHpBar.setFillColor(Color::Green);        //Color
    this->playerHpBar.setPosition(Vector2f(0.f,55.f));//Position


    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(Color(25,25,25,200));
    this->playerHpBarBack.setOutlineColor(Color::White);

}
void Game::initSystems(){
    this->points = 0;
    this->lives = 3;
}
void Game::initPlayer(){
    this->Player = new player();
    //Initializing player at the bottom in the middle
    Player->setPosition(this->window->getSize().x/2.f,
                        this->window->getSize().y);
}
void Game::initHelicopter(){
    //this->helicopter = new Helicopter(20.f, 20.f);
    //How long till new helicopter to appear
    this->spawnTimerMax = 50.f;
    this->spawnTimer = spawnTimerMax;
}
void Game::initShip(){
    this->spawnTimerMaxShips = 50.f;
    this->spawnTimerShips = spawnTimerMaxShips;
}
void Game::initFuel(){
    //How long till new fuel to appear
    //this->spawnTimerFuelMax = 50.f;
    //this->spawnTimerFuel = spawnTimerFuelMax;
}


//Constructor Destructor
Game::Game(){
    this -> initWindow(); //Always after variables
    this -> initWorld();
    this -> initTextures();
    this -> initGUI();
    this -> initSystems();
    this -> initPlayer();
    this -> initHelicopter();
    this -> initShip();
    this -> initFuel();
}
Game::~Game(){
    delete this->window;
    delete this->Player;
    delete this->mapArray;

    //Delete textures
    for (auto &i : this -> textures){
        delete i.second; //For each i we delete the second part that contains the actual texture
    }

    //Delete bullets
    for (auto *i : this->bullet){
        delete i;
    }

    //Delete helicopters
    for (auto *i : this->helicopters){
        delete i;
    }

    //Delete ships
    for (auto *i : this->ships){
        delete i;
    }

    //Delete fuels
    for (auto *i : this->fuels){
        delete i;
    }
}

//Public Functions
void Game::run(){
    while(this->window->isOpen()) {
        this->updatepollEvents();

        if(this->lives > 0){
            this->update();
        }
        this->render();
    }
}

// Update
void Game::updatepollEvents(){
    //Event Polling
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) { //according to type of event switch
            case Event::Closed: //When I click close
                this->window->close();
                break;
            case Event::KeyPressed:  //Case where key is pressed
                if (this->ev.key.code == Keyboard::Escape) //If key is Escape
                    this->window->close();
                break;
        }
    }
}
void Game::updateInput(){
    /*
     * Move player with keys, lose fuel when we accelerate and shoot
     * Generate bullet object when we press space
     */

    //Move Player
    int playerPosX = int(this->Player->getPos().x / 32);
    int playerPosY= int(this->Player->getPos().y / 32);
    int mapPosY = int((this->map.getPosition().y) / 32) + 20 - playerPosY;

    if (Keyboard::isKeyPressed(Keyboard::Right))
        //if check for collision then move
        if (this->mapArray[mapPosY][playerPosX + 3] >= 1) {
            this->Player->move(1.f, 0.f);
        }
    if (Keyboard::isKeyPressed(Keyboard::Left))
        //if check for collision then move
        if (this->mapArray[mapPosY][playerPosX - 1] >= 1) {
            this->Player->move(-1.f, 0.f);
        }
    //Move Mapshape at a higher/lower velocity when acc or dec
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->speed=this->speed*1.02f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->speed=this->speed/1.02f;

//    if (Keyboard::isKeyPressed(Keyboard::Up)) {
//        //When we accelerate we loose fuel
//        this->Player->setHp(this->Player->getHp() - (1.f));
//        this->Player->move(0.f, -1.f);
//    }
//    if (Keyboard::isKeyPressed(Keyboard::Down))
//        this->Player->move(0.f, 1.f);

    if (bulletTimer < 20) //Controls the amount of bullets per time (so as not to waste bullets)
        bulletTimer++;

    //Create Bullets, first we check if player can attack
    if (Keyboard::isKeyPressed(Keyboard::Space) && this->Player->canAttack() && bulletTimer >= 20){
        //When we shoot lose Fuel
        bulletTimer = 0;
        this->Player->setHp((this->Player->getHp())-5);

        //Shooting bullet. Create bullet and move forward
        this->bullet.push_back(new Bullet(this->textures["BULLET"],
                                          this->Player->getPos().x + this->Player->getBounds().width/2.f,
                                          this->Player->getPos().y,
                                          0.f, -1.f, 5.f));
    }
}
void Game::updateWorld() {
    this->map.move(sf::Vector2f(0, this->speed));
}
void Game::updateGUI(){
    //Update points
    stringstream ss;
    ss << "Points: " << this->points;
    this->pointText.setString(ss.str());

    //Update lives
    stringstream sslife;
    sslife << "Lives: " << this->lives;
    this->lifeText.setString(sslife.str());

    //Update player GUI. PlayerHPBar (only the front one)
    stringstream ssFuel;
    sslife << "Fuel: ";
    this->fuelText.setString(ssFuel.str());

    float hpPercent = static_cast<float>(this->Player->getHp())/this->Player->getHpMax();
    this->playerHpBar.setSize(Vector2f(300.f * hpPercent, //size of initial hbar width time percent
                                       this->playerHpBar.getSize().y)); //hbar height stays the same

    //If we empty fuel we lose 1 life
    if(this->Player->getHp() == 0.f){
        this->lives = this->lives - 1;
        this->Player->setHp(this->Player->getHpMax());
    }


}
void Game::updateCollision(){
    //Limiting boundaries so player can not move outside window. Snap it back
    //Left side
    if(this->Player->getBounds().left < 0.f){
        this->Player->setPosition(0.f, this->Player->getBounds().top);
    }
    //Right side
    if(this->Player->getBounds().left + Player->getBounds().width >= this->window->getSize().x){
        this->Player->setPosition(this->window->getSize().x - this->Player->getBounds().width, this->Player->getBounds().top);
    }
    //Top side
    if(this->Player->getBounds().top < 0.f){
        this->Player->setPosition(this->Player->getBounds().left, 0.f);
    }
    //Bottom side
    if(this->Player->getBounds().top + Player->getBounds().height >= this->window->getSize().y){
        this->Player->setPosition(this->Player->getBounds().left, this->window->getSize().y - this->Player->getBounds().height);
    }
}
void Game::updateBullets(){
    unsigned counter = 0;
    for (auto *bullet : this->bullet){
        bullet->update();

        //Bullet culling (removing something when it is not visible) outside of top screen
        if(bullet->getBounds().top + bullet->getBounds().height < 0.f){
            //Erasing bullet from vector
            delete this->bullet.at(counter);
            this->bullet.erase(this->bullet.begin() + counter);
            -- counter; //-1 (the one erased)

        }
        ++ counter;
    }
}
void Game::updateHelicopters() {
    //SPAWNING
    this -> spawnTimer += 0.5f; //IncreasingTimer
    //As soon as it reaches max (50) goes back to 0
    if(this->spawnTimer >= this->spawnTimerMax && helicopters.size()<3) {
        //new helicopter appears
        this->helicopters.push_back(new Helicopter(-100.f,
                                                   rand()% this->window->getSize().y-230.f));
        this->spawnTimer = 0.f;
    }

    unsigned counter = 0;
    //Moving helicopter
    for (auto *helicopter : this->helicopters){
        helicopter->update(); //Moves helicopter

        //HELICOPTER CULLING remove it out of screen
        if(helicopter->getBounds().left > this->window->getSize().x){
            //Erasing helicopter from vector
            delete this->helicopters.at(counter);
            this->helicopters.erase(this->helicopters.begin() + counter);
            -- counter; //-1 (the one erased)

        }
        //If helicopter touches player. Enemy player collision
        else if(helicopter->getBounds().intersects(this->Player->getBounds())){
            //Update lives
            this->lives = this->lives - 1;
            delete this->helicopters.at(counter);
            this->helicopters.erase(this->helicopters.begin() + counter);
            --counter;
        }
        ++ counter;
    }

}
void Game::updateShips(){
    //SPAWNING
    this -> spawnTimerShips += 0.5f; //IncreasingTimer
    //As soon as it reaches max (50) goes back to 0
    if(this->spawnTimerShips >= this->spawnTimerMaxShips && ships.size()<2) {
        //new ship appears
        this->ships.push_back(new Ship(rand()% 420 + 256, // delimit space for boats inside river
                                       -70)); // before appearing in window
        this->spawnTimerShips = 0.f;
    }

    unsigned counter_ship = 0;
    for (auto *ship : this->ships){
        ship->update(this->speed); //Moves ship

        //SHIPS CULLING remove if out of screen
        if(ship->getBounds().left > this->window->getSize().x){
            //Erasing ship from vector
            delete this->ships.at(counter_ship);
            this->ships.erase(this->ships.begin() + counter_ship);
            -- counter_ship; //-1 (the one erased)

        }

        if(ship->getBounds().top > this->window->getSize().y){
            //Erasing ship from vector
            delete this->ships.at(counter_ship);
            this->ships.erase(this->ships.begin() + counter_ship);
            -- counter_ship; //-1 (the one erased)

        }
        //If ship touches player. Enemy player collision
        else if(ship->getBounds().intersects(this->Player->getBounds())){
            //Update lives
            this->lives = this->lives - 1;
            delete this->ships.at(counter_ship);
            this->ships.erase(this->ships.begin() + counter_ship);
            --counter_ship;
        }
        ++ counter_ship;
    }
}
void Game::updateFuels() {

    //Adding new fuels only if less than 2 present
    if (fuels.size()<2) {
        //new fuel appears
        this->fuels.push_back(new Fuel(rand()% 420 + 250,
                                       -70));
    }

    //Fuel culling (removing something when it is not visible) outside of top screen
    unsigned counterFuel = 0;
    for (auto *fuel: this->fuels) {
        fuel->update(this->speed);

        if (fuel->getBounds().left > this->window->getSize().x) {
            //Erasing helicopter from vector
            delete this->fuels.at(counterFuel);
            this->fuels.erase(this->fuels.begin() + counterFuel);
            --counterFuel; //-1 (the one erased)
        }

        else if(fuel->getBounds().top > this->window->getSize().y){
            //Erasing ship from vector
            delete this->fuels.at(counterFuel);
            this->fuels.erase(this->fuels.begin() + counterFuel);
            -- counterFuel; //-1 (the one erased)

        }

        //If player touches fuel. Fill healthbar
        else if (fuel->getBounds().intersects(this->Player->getBounds())) {
            //Update healthbar
            this->Player->setHp(this->Player->getHp()+20);
            delete this->fuels.at(counterFuel);
            this->fuels.erase(this->fuels.begin() + counterFuel);
            --counterFuel;
        }
        ++counterFuel;
    }

}
void Game::updateCombat() {
    //HELICOPTERS GETTING KILLED

    //Update Helicopters
    for (int i = 0; i < this->helicopters.size(); ++i) {
        bool helicopter_removed = false; //Add boolean so Remove enemies outside screen doesn't crash
        //this->helicopters[i]->update();

        //Check if enemy hit by bullet for all bullets in array if they havent been removed (helicopter_removed==false)
        for (size_t k = 0; k < this->bullet.size() && helicopter_removed == false; k++) {
            //If the bullet at position k intersects with the bounds of active helicopter
            if (this->helicopters[i]->getBounds().intersects(this->bullet[k]->getBounds())) {

                //Update points
                this->points += this->helicopters[i]->getPoints();

                //Remove bullet and remove enemy
                delete this->helicopters[i];
                this->helicopters.erase(this->helicopters.begin() + i);//Remove helicopter at position i
                delete this->bullet[k];
                this->bullet.erase(this->bullet.begin() + k); //Remove bullet at position k
                helicopter_removed = true;
            }
        }
    }

    //SHIPS GETTING KILLED

    //Update Helicopters
    for (int i = 0; i < this->ships.size(); ++i) {
        bool ship_removed = false; //Add boolean so Remove enemies outside screen doesn't crash

        //Check if enemy hit by bullet for all bullets in array if they havent been removed (ship_removed==false)
        for (size_t k = 0; k < this->bullet.size() && ship_removed == false; k++) {
            //If the bullet at position k intersects with the bounds of active ship
            if (this->ships[i]->getBounds().intersects(this->bullet[k]->getBounds())) {

                //Update points
                this->points += this->ships[i]->getPoints();

                //Remove bullet and remove enemy
                delete this->ships[i];
                this->ships.erase(this->ships.begin() + i);//Remove helicopter at position i
                delete this->bullet[k];
                this->bullet.erase(this->bullet.begin() + k); //Remove bullet at position k
                ship_removed = true;
            }
        }
    }
}
void Game::update(){
    this->updateInput();
    if (this->map.getPosition().y > 16900){ // will reach to 520 row out of 550
        this->map.setPosition(0,0);
        this->updateWorld();
    }
    else{
        this->updateWorld();
    }
    this->Player->update();
    this->updateCollision();
    this->updateBullets();
    this->updateHelicopters();
    this->updateShips();
    this->updateFuels();
    this->updateCombat();//
    this->updateGUI(); //Call it after everything else

}

// Render
void Game::renderWorld() {
    this->window->draw(this->map);
}
void Game::renderGUI(){
    this->window->draw(this->pointText);
    this->window->draw(this->lifeText);
    this->window->draw(this->playerHpBarBack);
    this->window->draw(this->playerHpBar);
}
void Game::render(){
    /*
     * Renders the game objects
     * - clear old frame
     * - draw
     * - display
     */
    this->window->clear(); //clear old frame

    //Draw world
    this->renderWorld();

    //Render game objects

    //Player
    this->Player->render(*this->window);

    //Bullets
    for (auto *bullet : this->bullet){
        bullet->render(this->window);
    }

    //Helicopters
    for (auto *helicopter : this->helicopters){
        helicopter->render(this->window);
    }

    //Ships
    for (auto *ship : this->ships){
        ship->render(this->window);
    }

    //Fuels
    for (auto *fuel : this->fuels){
        fuel->render(this->window);
    }

    this->renderGUI();

    //Game over screen
    if(this->lives <= 0)
        this->window->draw(this->gameOverText);

    this->window->display(); //Tell app window is done drawing
}