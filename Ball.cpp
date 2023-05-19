//
// Created by adm on 19.05.2023.
//

#include "Ball.h"


Ball::Ball(float pos_X, float pos_Y) {
    shape.setPosition(pos_X, pos_Y);
    shape.setRadius(this->ball_radius);
    shape.setFillColor( Color::Red);

    //ustawienie położenie punktu odniesienia, czyli wskazanie na środek piłki
    shape.setOrigin(this->ball_radius, this->ball_radius);
}
const CircleShape& Ball::getShape() const {
    return shape;
}

void Ball::draw(RenderTarget &target, RenderStates state) const {
    target.draw(this->shape, state);
}

void Ball::update() {
    shape.move(this->velocity);

    if(this->left()<0)
    {
        velocity.x =ball_velocity;
    }
    else if(this->right()>1000) //ZMIENIC TO 1000!!!!
    {
        velocity.x = -ball_velocity;
    }

    if(this->top()<2*ball_radius)
    {
        velocity.y =ball_velocity;
    }
    else if(this->bottom()>999-2*ball_radius) //ZMIENIC TO !!!! jakos przekzazc szerokosc okna aplikacji
    {
        velocity.y = -ball_velocity;
    }

}

float Ball::left() {
    return shape.getPosition().x - shape.getRadius();
}
float Ball::right() {
    return shape.getPosition().x + shape.getRadius();
}
float Ball::top() {
    return shape.getPosition().y + shape.getRadius();
}
float Ball::bottom() {
    return shape.getPosition().y - shape.getRadius();
}
