#include <SFML/Graphics.hpp>
#include "game.h"

//so, creating window, creting game, drawing, updating, nothing special at all
int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Foxes");

    Game game = Game(&window);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
                game.click(&event);
            else if(event.type == sf::Event::MouseMoved)
                game.mouseMove(&event);
            // "close requested" event: we close the window
            else if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        game.update();
        game.draw();

        window.display();
    }

    return 0;
}
