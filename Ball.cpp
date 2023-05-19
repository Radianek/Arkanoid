//
// Created by adm on 19.05.2023.
//

#include "Ball.h"


Ball::Ball(float pos_X, float pos_Y) {
    shape.setPosition(pos_X, pos_Y);
    shape.setRadius(this->ball_radius);
    shape.setFillColor( Color::Red);
    shape.setOrigin(this->ball_radius, this->ball_radius); //ustawienie położenie punktu odniesienia, czyli wskazanie na środek piłki
}
const CircleShape& Ball::getShape() const {
    return shape;
}

void Ball::draw(RenderTarget &target, RenderStates state) const {
    target.draw(this->shape, state);
}

