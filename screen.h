#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "cell.h"
//definition of all screen classes we use
class Game;

bool pointInRect(int, int, int, int, int, int);

class Screen{
protected:
    Game *game;
    sf::Sprite bg;

public:
    virtual void restart();
    virtual void mouseMove(sf::Event*);
    virtual void draw(sf::RenderWindow*) = 0;
    virtual void update() = 0;
    virtual void click(sf::Event*) = 0;
};

class WinScreen : public Screen{
public:
    WinScreen(Game*);
    void draw(sf::RenderWindow*);
    void update();
    void click(sf::Event*);
};

class FoundedScreen : public Screen{
public:
    FoundedScreen(Game*);
    void draw(sf::RenderWindow*);
    void update();
    void click(sf::Event*);
};

class MainMenu : public Screen{
public:
    MainMenu(Game*);
    void draw(sf::RenderWindow*);
    void update();
    void click(sf::Event*);
};

class GameScreen : public Screen{
private:
    Screen *winScreen;
    Screen *loseScreen;
    Screen *foundedScreen;
    Cell field[10][10];
    Cell *lastMarked;
    int vraw;
    int hraw;
    int mdiag;
    int adiag;
    int found;
public:
    GameScreen(Game*);
    void draw(sf::RenderWindow*);
    void update();
    void mouseMove(sf::Event*);
    void click(sf::Event*);
    void restart();
};

class LoseScreen : public Screen{
public:
    LoseScreen(Game*);
    void draw(sf::RenderWindow*);
    void update();
    void click(sf::Event*);
};

class HowToPlay : public Screen{
public:
    HowToPlay(Game*);
    void draw(sf::RenderWindow*);
    void update();
    void click(sf::Event*);
};
#endif // SCREEN_H_INCLUDED
