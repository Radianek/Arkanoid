#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(640, 480), "Arcanoid");
    window.setFramerateLimit(60);
    Event event;

    while(window.isOpen())
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
