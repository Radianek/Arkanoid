#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(640, 480), "Arcanoid");
    window.setFramerateLimit(60);
    Event event;

    while(true)
    {
        window.clear( Color::Black);
        window.pollEvent(event);

        if(event.type == Event::Closed)
        {
            window.close();
            break;
        }


        window.display();
    }


}
/*
    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition(100.f, 100.f);
    shape.setFillColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
*/