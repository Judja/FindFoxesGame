 #include "screen.h"
#include "game.h"
#include <ctime>

void Screen::mouseMove(sf::Event *event){

}

void Screen::restart(){

}
////////////////

WinScreen::WinScreen(Game *g){
    game = g;
    bg.setTexture(game->atlas);
    bg.setTextureRect(sf::IntRect(800, 600, 400, 250));
}

void WinScreen::click(sf::Event *event){
    if(pointInRect((*event).mouseButton.x, (*event).mouseButton.y, 232, 315, 160, 70)){
        game->setScreen(game->gameScreen);
        game->gameScreen->restart();
    }
    else if(pointInRect((*event).mouseButton.x, (*event).mouseButton.y, 416, 315, 140, 70)){
        game->setScreen(game->mainMenu);
        game->gameScreen->restart();
    }
}

void WinScreen::draw(sf::RenderWindow *window){
    game->gameScreen->draw(window);
    bg.setPosition(200, 170);
    window->draw(bg);
}

void WinScreen::update(){}

LoseScreen::LoseScreen(Game *g){
    game = g;
    bg.setTexture(game->atlas);
    bg.setTextureRect(sf::IntRect(800, 850, 400, 250));
}

void LoseScreen::click(sf::Event *event){
    if(pointInRect((*event).mouseButton.x, (*event).mouseButton.y, 232, 315, 160, 70)){
        game->setScreen(game->gameScreen);
        game->gameScreen->restart();
    }
    else if(pointInRect((*event).mouseButton.x, (*event).mouseButton.y, 416, 315, 140, 70)){
        game->setScreen(game->mainMenu);
        game->gameScreen->restart();
    }
}

void LoseScreen::draw(sf::RenderWindow *window){
    game->gameScreen->draw(window);
    bg.setPosition(200, 170);
    window->draw(bg);
}

void LoseScreen::update(){}
///////////////////////////////////////
FoundedScreen::FoundedScreen(Game *g){
    game = g;
    bg.setTexture(game->atlas);
    bg.setTextureRect(sf::IntRect(800, 1100, 400, 100));
}

void FoundedScreen::click(sf::Event *event){
    game->setScreen(game->gameScreen);
}

void FoundedScreen::draw(sf::RenderWindow *window){
    game->gameScreen->draw(window);
    bg.setPosition(200, 250);
    window->draw(bg);
}

void FoundedScreen::update(){}

/////////////////////////////////
void MainMenu::click(sf::Event *event){
    if(pointInRect((*event).mouseButton.x, (*event).mouseButton.y, 570, 500, 200, 60))
        game->getWindow()->close();
    else if(pointInRect((*event).mouseButton.x, (*event).mouseButton.y, 250, 155, 300, 80))
        game->setScreen(game->gameScreen);
    else if(pointInRect((*event).mouseButton.x, (*event).mouseButton.y, 250, 400, 300, 80))
        game->setScreen(game->howToPlay);
}

MainMenu::MainMenu(Game *g){
    game = g;
    bg.setTexture(game->atlas);
    bg.setTextureRect(sf::IntRect(0, 0, 800, 600));
}

void MainMenu::update(){}

void MainMenu::draw(sf::RenderWindow *window){
    window->clear(sf::Color::White);
    window->draw(bg);
}

bool pointInRect(int xp, int yp, int xr, int yr, int wr, int hr){
    if(xp > xr && xp < xr+wr && yp>yr && yp<yr+hr)
        return true;
    return false;
}
//////////////////////////////
HowToPlay::HowToPlay(Game *g){
    game = g;
    bg.setTexture(game->atlas);
    bg.setTextureRect(sf::IntRect(0, 600, 800, 600));
}

void HowToPlay::click(sf::Event *event){
    if(pointInRect((*event).mouseButton.x, (*event).mouseButton.y, 30, 503, 200, 70))
        game->setScreen(game->mainMenu);
}

void HowToPlay::update(){}

void HowToPlay::draw(sf::RenderWindow *window){
    window->clear(sf::Color::Blue);
    window->draw(bg);
}
////////////////////////////////
GameScreen::GameScreen(Game *g){
    game = g;
    bg.setTexture(game->atlas);
    bg.setTextureRect(sf::IntRect(0, 1200, 800, 600));
    winScreen = new WinScreen(g);
    loseScreen = new LoseScreen(g);
    foundedScreen = new FoundedScreen(g);
}

void GameScreen::click(sf::Event *event){
    int x = (*event).mouseButton.x;
    int y = (*event).mouseButton.y;
    if(pointInRect(x, y, 580, 503, 180, 70))
        game->setScreen(game->mainMenu);
    else if(pointInRect(x, y, 50, 50, 500, 500)){
        //game here
        x=(x-50)/50;
        y=(y-50)/50;

        lastMarked = NULL;

        if(field[y][x].foxes){
            found+=field[y][x].foxes;
            field[y][x]. foxes = 0;
            game->setScreen(foundedScreen);
            if(found == 8){
                game->setScreen(winScreen);
            }
        }

        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                field[i][j].marked = false;
            }
        }

        vraw = 0;
        for(int i = 0; i < 10; i++){
            field[i][x].marked = true;
            vraw += field[i][x].foxes;
        }
        hraw = 0;
        for(int i = 0; i < 10; i++){
            field[y][i].marked = true;
            hraw += field[y][i].foxes;
        }
        mdiag = 0;
        adiag = 0;
        if(y>x){
            for(int j = y-x; j < 10; j++){
                field[j][j-y+x].marked = true;
                mdiag += field[j][j-y+x].foxes;
            }
        }
        else{
            for(int i = x-y; i < 10; i++){
                field[i-x+y][i].marked = true;
                mdiag += field[i-x+y][i].foxes;
            }
        }
        if(y>10-x){
            for(int j = x-9+y; j < 10; j++){
                field[x+y-j][j].marked = true;
                adiag += field[x+y-j][j].foxes;
            }
        }
        else{
            for(int j = x+y; j >= 0; j--){
                field[x+y-j][j].marked = true;
                adiag += field[x+y-j][j].foxes;
            }
        }
    }
}

void GameScreen::mouseMove(sf::Event *event){
    int x = (*event).mouseMove.x;
    int y = (*event).mouseMove.y;
    if(pointInRect(x, y, 50, 50, 500, 500)){
        x=(x-50)/50;
        y=(y-50)/50;
        if(lastMarked != NULL){
            lastMarked->marked = false;
        }
        if(field[y][x].marked){
            lastMarked = NULL;
        }
        else{
            lastMarked = &field[y][x];
            lastMarked->marked = true;
        }
    }
}

void GameScreen::update(){}

void GameScreen::draw(sf::RenderWindow *window){
    sf::RectangleShape rect(sf::Vector2f(50, 50));
    window->clear(sf::Color::Blue);

    window->draw(bg);

    game->numbs[found].setPosition(640, 90);
    window->draw(game->numbs[found]);

    game->numbs[adiag].setPosition(626, 133);
    window->draw(game->numbs[adiag]);

    game->numbs[mdiag].setPosition(626, 165);
    window->draw(game->numbs[mdiag]);

    game->numbs[hraw].setPosition(626, 197);
    window->draw(game->numbs[hraw]);

    game->numbs[vraw].setPosition(626, 229);
    window->draw(game->numbs[vraw]);

    rect.setFillColor(sf::Color(0, 0, 30, 64));

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(field[i][j].marked){
                rect.setPosition(50+j*50, 50+i*50);
                window->draw(rect);
            }
        }
    }

    rect.setSize(sf::Vector2f(500, 1));
    rect.setFillColor(sf::Color::Green);
    for(int i = 0; i < 11; i++){
        rect.setPosition(50, 49+i*50);
        window->draw(rect);
    }
    rect.setSize(sf::Vector2f(1, 500));
        for(int i = 0; i < 11; i++){
        rect.setPosition(49+i*50, 50);
        window->draw(rect);
    }
}

void GameScreen::restart(){
    srand(time(NULL));
    lastMarked = NULL;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            field[i][j].marked = false;
            field[i][j].foxes = 0;
        }
    }

    for(int i = 0; i < 8; i++){
        field[rand()%10][rand()%10].foxes++;
    }

    found = 0;
    adiag = 0;
    mdiag = 0;
    vraw = 0;
    hraw = 0;
}
///////////////////////////////
