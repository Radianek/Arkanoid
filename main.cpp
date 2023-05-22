#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "Menu.h"
#include "Block.h"

using namespace std;
using namespace sf;


int main()
{
    int menu_options =1;
    /***************************************************************
     *          menu_options           *          Function         *
     * ____________________________________________________________*
     *            -1                   *         close             *
     *             0                   *         Game              *
     *             1                   *         MainMenu          *
     *             2                   *         instructions      *
     *             3                   *                           *
     ***************************************************************
     */

    Ball ball(500, 500);
    Paddle paddle(950, 950);
    RenderWindow window (VideoMode(1650, 1050),"Arcanoid");
    Menu menu(1920, 1080);
    Texture mainmenu_photo;
    Texture instruction_photo;
    instruction_photo.loadFromFile("instrukcja.png");
    mainmenu_photo.loadFromFile("obraz.png");
    Sprite photo;
    photo.setTexture(mainmenu_photo);
    window.setFramerateLimit(60);
    Event event;
    unsigned blocks_x {15}, blocks_y{4}, block_width{100}, block_height{60};

    vector<Block> blocks;
    for(int i = 0; i< blocks_y;i++)
    {
        for(int j= 0; j < blocks_x; j++)
        {
            blocks.emplace_back((j+1)*(block_width+5),(i+1)*(block_height+5), block_width, block_height);
        }
    }

    while(true)
    {
        if(menu_options ==1)
        {
            while(window.isOpen())
            {
                while (window.pollEvent(event))
                {
                    if(event.type==Event::Closed)
                    {
                        window.close();
                        return 0;
                    }

                    if(event.type==Event::KeyPressed)
                    {
                        if(event.key.code == Keyboard::Up)
                        {
                            menu.MoveUp();
                        }
                        else if(event.key.code == Keyboard::Down)
                        {
                            menu.MoveDown();
                        }
                        else if(event.key.code==Keyboard::Return)
                        {
                            if(menu.pressed()==0)
                            {
                                menu_options=0;
                            }
                            if(menu.pressed()==1)
                            {
                                menu_options=2;
                            }
                            if(menu.pressed()==2)
                            {
                                menu_options=-1;
                            }
                        }
                    }


                }
                window.clear();
                if(menu_options != 1)
                {
                    break;
                }
                window.draw(photo);
                menu.draw(window);
                window.display();
            }
            if(menu_options == -1)
            {
                window.close();
                break;
            }
            else if(menu_options == 0)
            {
                while(window.isOpen())
                {
                    window.clear( Color::Black);
                    window.pollEvent(event);

                    if(event.type == Event::Closed)
                    {
                        window.close();
                        return 0;
                    }
                    ball.update();
                    paddle.update();
                    ball.update();
                    paddle.update();

                    window.draw(ball.getShape());
                    window.draw(paddle.getShape());

                    for(auto& block:blocks)
                    {
                        window.draw(block.getShape());
                    }
                    window.display();
                }
            }
            else if (menu_options == 2)
            {
                while (window.isOpen())
                {
                    window.clear(Color::Black);
                    window.pollEvent(event);

                    if (event.type == Event::Closed)
                    {
                        window.close();
                        return 0;
                    }

                    // Rysowanie obrazka instrukcji
                    Sprite instructionSprite(instruction_photo);

                    // Ustawienie pozycji na środku okna
                    float posX = (window.getSize().x - instructionSprite.getGlobalBounds().width) / 2.f;
                    float posY = (window.getSize().y - instructionSprite.getGlobalBounds().height) / 2.f;
                    instructionSprite.setPosition(posX, posY);

                    window.draw(instructionSprite);

                    // Rysowanie przycisku "Back"
                    RectangleShape backButton(Vector2f(100.f, 40.f));
                    backButton.setFillColor(Color::Red);
                    backButton.setPosition(posX/5 + instructionSprite.getGlobalBounds().width - 7*backButton.getSize().x, posY + instructionSprite.getGlobalBounds().height - backButton.getSize().y - 200.f);
                    window.draw(backButton);

                    // Tworzenie tekstu "Back"
                    Font font;
                    if (!font.loadFromFile("Bambuchinnox.ttf")) // Ścieżka do pliku czcionki
                    {
                        // Obsługa błędu wczytywania czcionki
                        // Możesz użyć innej czcionki lub zwrócić komunikat o błędzie
                    }

                    Text backText("Back", font, 20); // Tekst "Back" z czcionką i rozmiarem 20
                    backText.setFillColor(Color::White);
                    backText.setPosition(backButton.getPosition().x + backButton.getSize().x / 2.f - backText.getGlobalBounds().width / 2.f, backButton.getPosition().y + backButton.getSize().y / 3.f - backText.getGlobalBounds().height / 2.f);
                    window.draw(backText);

                    window.display();

                    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                    {
                        menu_options = 1; // Przejście do menu głównego po naciśnięciu klawisza Escape
                        break;
                    }

                    if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
                    {
                        // Sprawdzenie, czy kliknięcie myszką nastąpiło na przycisku "Back"
                        Vector2f mousePosition = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));

                        if (backButton.getGlobalBounds().contains(mousePosition))
                        {
                            menu_options = 1; // Przejście do menu głównego po kliknięciu przycisku "Back"
                            break;
                        }
                    }
                }
            }
        }
    }
}

