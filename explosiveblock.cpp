//
// Created by wawru on 05.06.2023.
//

#include "explosiveblock.h"

using namespace std;

explosiveblock::explosiveblock(float pos_X, float pos_Y, float width, float height) : Block(pos_X, pos_Y, width, height)
{
    shape.setPosition(pos_X, pos_Y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color{48, 213, 200});
    shape.setOrigin(width/2.f, height/2.f);
    srand(static_cast<unsigned>(time(nullptr)));

}


void explosiveblock::draw_number()
{
    srand(static_cast<unsigned>(time(nullptr)));
    draw_number_x = (rand() % 13) +1;
    draw_number_y = (rand() % 2) +1;
}
void explosiveblock::set_position()
{
    shape.setPosition(((draw_number_x+1)*105),(((draw_number_y+1)*65)));
}

