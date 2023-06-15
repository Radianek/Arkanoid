//
// Created by wawru on 13.06.2023.
//

#ifndef PROJEKT_MOVINGBLOCK_H
#define PROJEKT_MOVINGBLOCK_H

#include "Block.h"


class Movingblock : public Block{
public:
    Movingblock(float pos_X, float pos_Y, float width, float height);
    void update();
    void stop();
    void move();
    void movingblock_stop_game();
    void restore_velocity();
    Vector2f get_position();
    bool stopped = false;
    float movingblock_velocity_helper_x;

private:
    float movingblock_velocity{3.0f};
    Vector2f velocity{movingblock_velocity, 0};

};


#endif //PROJEKT_MOVINGBLOCK_H
