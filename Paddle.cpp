//
// Created by adm on 19.05.2023.
//

#include "Paddle.h"

Paddle::Paddle(float pos_X, float pos_Y) {
    shape.setPosition(pos_X, pos_Y);
    shape.setSize(sf::Vector2f(this->paddle_width,this->paddle_height));
    shape.setFillColor( sf::Color::Green);

    //ustawienie położenie punktu odniesienia
    shape.setOrigin(this->paddle_width/2.f, this->paddle_height/2.f);
}

const sf::RectangleShape& Paddle::getShape() const {
    return shape;
}

void Paddle::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    target.draw(this->shape, state);
}

void Paddle::update() {
    this->shape.move(this->velocity);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)&& this->left() >0){
        velocity.x= -paddle_velocity;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)&& this->right() <1650) //ZMIENIC TO !!!! jakos przekzazc szerokosc okna aplikacji
    {
     velocity.x= paddle_velocity;
    }
    else{
        velocity.x=0;
    }
}
void Paddle::stop_paddle()
{
    paddle_velocity = 0;
}

float Paddle::left() {
    return shape.getPosition().x - shape.getSize().x/2.f;
}
float Paddle::right() {
    return shape.getPosition().x + shape.getSize().x/2.f;
}
float Paddle::top() {
    return shape.getPosition().y - shape.getSize().y/2.f;
}
float Paddle::bottom() {
    return shape.getPosition().y + shape.getSize().y/2.f;
}
sf::Vector2f Paddle::getPosition()
{
    return shape.getPosition();
}
void Paddle::reset_paddle()
{
    paddle_velocity = 7.0f;
    shape.setPosition(825, 950);
}
void Paddle::restore_velocity()
{
    paddle_velocity = 7.0f;
}