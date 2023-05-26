//
// Created by adm on 20.05.2023.
//

#include "Menu.h"


Menu::Menu(float width, float height)
{
    font.loadFromFile("Bambuchinnox.ttf");

    mainmenu[0].setFont(font);
    mainmenu[0].setFillColor(Color{160, 32, 240});
    mainmenu[0].setString("Play");
    mainmenu[0].setCharacterSize(90);
    mainmenu[0].setPosition(Vector2f(width/3,height/(3)));

    mainmenu[1].setFont(font);
    mainmenu[1].setFillColor(Color{255,255,255});
    mainmenu[1].setString("Instructions");
    mainmenu[1].setCharacterSize(90);
    mainmenu[1].setPosition(Vector2f(width/3,height/(3)+200));

    mainmenu[2].setFont(font);
    mainmenu[2].setFillColor(Color{255,255,255});
    mainmenu[2].setString("Exit");
    mainmenu[2].setCharacterSize(90);
    mainmenu[2].setPosition(Vector2f(width/3,height/(3)+400));

    end_menu[0].setFont(font);
    end_menu[0].setFillColor(Color{255,255,255});
    end_menu[0].setString("New game");
    end_menu[0].setCharacterSize(50);
    end_menu[0].setPosition(Vector2f(412 - end_menu[0].getGlobalBounds().width/2.f ,750));

    end_menu[1].setFont(font);
    end_menu[1].setFillColor(Color{255,255,255});
    end_menu[1].setString("Back to menu");
    end_menu[1].setCharacterSize(50);
    end_menu[1].setPosition(Vector2f(824 - end_menu[1].getGlobalBounds().width/2.f ,750));

    end_menu[2].setFont(font);
    end_menu[2].setFillColor(Color{255,255,255});
    end_menu[2].setString("Close game");
    end_menu[2].setCharacterSize(50);
    end_menu[2].setPosition(Vector2f(1237 - end_menu[2].getGlobalBounds().width/2.f ,750));


    selected = 0;
}

Menu::~Menu() {}

void Menu::setSelected(int n)
{
    selected = n;
}

void Menu::draw(RenderWindow &window)
{
    for(int i=0;i<3;i++)
    {
        window.draw(mainmenu[i]);
    }
}

void Menu::draw_end_menu(sf::RenderWindow &window)
{
    for(int i=0; i<3; i++)
    {
        window.draw(end_menu[i]);
    }
}

void Menu::MoveDown()
{
    if(selected + 1 <=3)
    {
        mainmenu[selected].setFillColor(Color{255, 255, 255});
        selected++;
        if(selected ==3)
        {
            selected= 0;
        }
        mainmenu[selected].setFillColor(Color{160, 32, 240});
    }
}

void Menu::MoveUp()
{
    if(selected-1>=-1)
    {
        mainmenu[selected].setFillColor(Color{255, 255, 255});
        selected--;
        if(selected==-1)
        {
            selected= 2;
        }
        mainmenu[selected].setFillColor(Color{160, 32, 240});
    }
}

void Menu::MoveLeft()
{
    if(selected-1>=-1)
    {
        end_menu[selected].setFillColor(Color{255, 255, 255});
        selected--;
        if(selected==-1)
        {
            selected = 2;
        }
        end_menu[selected].setFillColor(Color{160, 32, 240});
    }
}

void Menu::MoveRight()
{
    if(selected +1 <=3)
    {
        end_menu[selected].setFillColor(Color{255, 255, 255});
        selected++;
        if (selected == 3)
        {
            selected = 0;
        }
        end_menu[selected].setFillColor(Color{160, 32, 240});
    }
}
void Menu::all_on_white()
{
    for(int i=0; i<3; i++)
    {
        end_menu[i].setFillColor(Color{255,255,255});
        mainmenu[i].setFillColor(Color{255,255,255});
    }
}
