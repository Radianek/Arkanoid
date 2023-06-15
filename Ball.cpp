//
// Created by adm on 19.05.2023.
//

#include "Ball.h"


Ball::Ball(float pos_X, float pos_Y) {
    shape.setPosition(pos_X, pos_Y);
    shape.setRadius(this->ball_radius);
    shape.setFillColor(Color::Red);
    //ustawienie położenie punktu odniesienia, czyli wskazanie na środek piłki
    shape.setOrigin(this->ball_radius, this->ball_radius);
}

const CircleShape &Ball::get_shape() const {
    return shape;
}

void Ball::draw(RenderTarget &target, RenderStates state) const {
    target.draw(this->shape, state);
}

void Ball::update() {
    shape.move(this->velocity);

    if (this->left() < 0) {
        velocity.x = ball_velocity;
    } else if (this->right() > 1650) //ZMIENIC TO !!!! jakos przekzazc szerokosc okna aplikacji
    {
        velocity.x = -ball_velocity;
    }

    if (this->top() < 2 * ball_radius) {
        velocity.y = ball_velocity;
    } else if (this->bottom() > 1070 - 2 * ball_radius) //ZMIENIC TO !!!! jakos przekzazc szerokosc okna aplikacji
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
    return shape.getPosition().y - shape.getRadius();
}

float Ball::bottom() {
    return shape.getPosition().y + shape.getRadius();
}


void Ball::move_down_ball() {
    this->velocity.y = ball_velocity;
}

void Ball::move_up_ball() {
    this->velocity.y = -ball_velocity;
}

void Ball::move_right_ball() {
    this->velocity.x = ball_velocity;
}

void Ball::move_left_ball() {
    this->velocity.x = -ball_velocity;
}

void Ball::under_paddle() {
    this->shape.setFillColor(Color::Black);
    this->velocity.x = 0;
    this->velocity.y = 0;


}

void Ball::stop_game() {
    if (Keyboard::isKeyPressed(Keyboard::P)) {
        static bool ball_stopped = false;
        is_stopped = true;
        if (!ball_stopped) {
            ball_velocity_helper_x = this->velocity.x;
            ball_velocity_helper_y = this->velocity.y;
            this->velocity.x = 0;
            this->velocity.y = 0;
            ball_stopped = true;
        } else {
            this->velocity.x = ball_velocity_helper_x;
            this->velocity.y = ball_velocity_helper_y;
            ball_stopped = false;
            is_stopped = false;

        }
    }
}

Vector2f Ball::getPosition() {
    return shape.getPosition();
}

void Ball::reset_ball() {
    shape.setFillColor(Color::Red);
    shape.setPosition(825, 525);
    this->velocity.x = 0.0f;
    this->velocity.y = 5.0f;
}