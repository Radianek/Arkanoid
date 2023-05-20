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