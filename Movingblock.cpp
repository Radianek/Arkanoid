//
// Created by wawru on 13.06.2023.
//

#include "Movingblock.h"

using namespace std;

Movingblock::Movingblock(float pos_X, float pos_Y, float width, float height) : Block(pos_X, pos_Y, width, height)
{
    shape.setPosition(pos_X, pos_Y);
    shape.setSize(Vector2f(width, height));
    shape.setFillColor(Color{128,128,128});
    shape.setOrigin((width/ 2.f), (height/2.f));
}

void Movingblock::update(){
    this->shape.move(this->velocity);
    if(this->left() == 0 ){
        velocity.x = movingblock_velocity;
    }else if (this->right() == 1630){
        velocity.x = -movingblock_velocity;
    }
}
void Movingblock::stop(){
    movingblock_velocity_helper_x = this->velocity.x;
    this->velocity.x = 0;

}
void Movingblock::move(){
    movingblock_velocity = 3.0f;
    velocity.x = movingblock_velocity;
}
void Movingblock::restore_velocity() {
    movingblock_velocity = 3.0f;
}
Vector2f Movingblock::get_position() {
    return shape.getPosition();
}
void Movingblock::movingblock_stop_game() {
        static bool block_stopped = false;
        stopped = true;
        if (!block_stopped) {
            this->movingblock_velocity_helper_x = this->velocity.x;
            this->velocity.x = 0;
            block_stopped = true;
        } else {
            this->velocity.x = this->movingblock_velocity_helper_x;
            block_stopped = false;
            stopped = false;

        }
    }
