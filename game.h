#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>

class Screen;

//its our Game class definition
//every game has one Game class, but one Game class has several screens
//Game is just a container, gathering everything together, all logic is implemented in screens
class Game{
private:
    sf::RenderWindow *window;
    Screen *screen;
public:
    Screen *mainMenu;
    Screen *gameScreen;
    Screen *howToPlay;
    sf::Texture atlas;
    sf::Sprite numbs[10];

    Game(sf::RenderWindow*);
    void draw();
    void update();
    void click(sf::Event*);
    void mouseMove(sf::Event*);
    void setScreen(Screen*);
    sf::RenderWindow* getWindow();
};

#endif // GAME_H_INCLUDED
