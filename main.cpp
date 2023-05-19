#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.h"


using namespace std;
using namespace sf;

int main()
{
    Ball ball(500, 500);
    RenderWindow window(sf::VideoMode(1000, 1000), "Arcanoid");
    window.setFramerateLimit(60);
    Event event;

    while(window.isOpen())
    {
        // Wyczyszczenie zawartości okna, ustawienie czarnego tła
        window.clear( Color::Black);

        // Pobieranie zdarzeń związanych z oknem
        window.pollEvent(event);

        if(event.type == Event::Closed)
        {
            window.close();
            break;
        }
        ball.update();

        // Pobranie kształtu piłki i przekazanie go do window.draw()
        window.draw(ball.getShape());

        window.display();
    }

}
