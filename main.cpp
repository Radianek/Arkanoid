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
        window.clear( Color::Black);// Wyczyszczenie zawartości okna, ustawienie czarnego tła
        window.pollEvent(event);// Pobieranie zdarzeń związanych z oknem

        if(event.type == Event::Closed)
        {
            window.close();
            break;
        }
        window.draw(ball.getShape());// Pobranie kształtu piłki i przekazanie go do metody window.draw()
        window.display();
    }

}
