//
// Created by wawru on 05.06.2023.
//

#ifndef PROJEKT_EXPLOSIVEBLOCK_H
#define PROJEKT_EXPLOSIVEBLOCK_H

#include "Block.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

class Explosiveblock : public Block {
public:

    Explosiveblock(float pos_X, float pos_Y, float width, float height);  // explosive block constructor
    void draw_number();     //function that draw a number
    void set_position();    //function that set position of explosive block
    float draw_number_x;    //variable that stores the drawn number
    float draw_number_y;    //variable that stores the drawn number


};


#endif //PROJEKT_EXPLOSIVEBLOCK_H
