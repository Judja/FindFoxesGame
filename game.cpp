#include "game.h"
#include "screen.h"

//So, game is our main object, which is always updating and beind drawn
//But game's update, draw, click and mousemove methods just call CurrentScreen draw, click, etc, methods
//It allows different sreen to work and implement different logic independently
Game::Game(sf::RenderWindow* w){
    window = w;
    mainMenu = new MainMenu(this);
    gameScreen = new GameScreen(this);
    //we use Screen.restart method to init screen
    gameScreen->restart();
    howToPlay = new HowToPlay(this);
    atlas.loadFromFile("atlas.png");
    for(int i = 0; i < 10; i++){
        numbs[i].setTexture(atlas);
        numbs[i].setTextureRect(sf::IntRect(800, i*32, 32, 32));
    }
    setScreen(mainMenu);
}

void Game::draw(){
    screen->draw(window);
}

void Game::update(){
    screen->update();
}

void Game::click(sf::Event *event){
    screen->click(event);
}

void Game::mouseMove(sf::Event* event){
    screen->mouseMove(event);
}

void Game::setScreen(Screen* scr){
    screen = scr;
}

sf::RenderWindow* Game::getWindow(){
    return window;
}
