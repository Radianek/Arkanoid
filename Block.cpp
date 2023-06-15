//
// Created by adm on 19.05.2023.
//

#include "Block.h"

Block::Block(float pos_X, float pos_Y, float width, float height) {
    shape.setPosition(pos_X, pos_Y);
    shape.setSize(Vector2f(width, height));
    shape.setFillColor(Color{184, 3, 255});
    shape.setOrigin(width / 2.f, height / 2.f);
}

const RectangleShape &Block::get_shape() const {
    return shape;
}


void Block::draw(RenderTarget &target, RenderStates state) const {
    target.draw(this->shape, state);
}

float Block::left() {
    return shape.getPosition().x - shape.getSize().x / 2.f;
}

float Block::right() {
    return shape.getPosition().x + shape.getSize().x / 2.f;
}

float Block::top() {
    return shape.getPosition().y - shape.getSize().y / 2.f;
}

float Block::bottom() {
    return shape.getPosition().y + shape.getSize().y / 2.f;
}

bool Block::is_destroyed() {
    return this->destroyed;
}

void Block::destroy() {
    this->destroyed = true;
    points++;
}

void Block::restore() {
    this->destroyed = false;
}

Vector2f Block::position() {
    return shape.getPosition();
}

Vector2f Block::size() {
    return shape.getSize();
}

