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
    mainmenu_photo.loadFromFile("obraz.jpg");
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
                        break;
                    }

                    if(event.type==Event::KeyPressed)
                    {
                        if(event.key.code == Keyboard::Up)
                        {
                            menu.MoveUp();
                        }
                    }
                    if(event.type==Event::KeyPressed)
                    {
                        if(event.key.code == Keyboard::Down)
                        {
                            menu.MoveDown();
                        }
                        if(event.key.code==Keyboard::Return)
                        {
                            if(menu.pressed()==0)
                            {
                                menu_options=0;
                            }
                            if(menu.pressed()==1)
                            {
                                menu_options=1;
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
            if(menu_options == 0)
            {
                while(window.isOpen())
                {
                    window.clear( Color::Black);
                    window.pollEvent(event);

                    if(event.type == Event::Closed)
                    {
                        window.close();
                        break;
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
        }
    }
}

